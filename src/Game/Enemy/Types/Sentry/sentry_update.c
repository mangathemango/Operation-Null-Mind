/**
 * @file sentry_update.c
 * @brief Implements update logic for Sentry enemy type
 *
 * Contains the AI behavior and state updates for the Sentry enemy.
 *
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_sentry.h>
#include <player.h>
#include <time_system.h>
#include <random.h>
#include <circle.h>
#include <math.h>

void Sentry_UpdateGun(EnemyData* data) {
    SentryConfig* config = (SentryConfig*)data->config;
    GunData* gun = &config->gun;
    Vec2 muzzlePosition = gun->config.muzzlePosition;
    Vec2 casingPosition = gun->config.ejectionPosition;

    // Flip the gun's sprite if mouse is on the left side of the player
    if (player.state.position.x < gun->state.position.x) {
        gun->state.flip = SDL_FLIP_VERTICAL;
        gun->state.rotationCenter = (SDL_Point) {
            gun->config.gripPosition.x, 
            gun->animData.spriteSize.y - gun->config.gripPosition.y,
        };
        muzzlePosition.y = gun->animData.spriteSize.y - muzzlePosition.y; 
        casingPosition.y = gun->animData.spriteSize.y - casingPosition.y;
        gun->resources.casingParticleEmitter->direction = Vec2_RotateDegrees(Vec2_Right, gun->state.angle + 135);
    } else {
        gun->state.flip = SDL_FLIP_NONE;
        gun->state.rotationCenter = (SDL_Point) {
            gun->config.gripPosition.x,
            gun->config.gripPosition.y
        }; 
        gun->resources.casingParticleEmitter->direction = Vec2_RotateDegrees(Vec2_Right, gun->state.angle - 135);
    }

    // Update gun's position
    gun->state.position = Vec2_Subtract(
        data->state.position,
        (Vec2) {
            gun->state.rotationCenter.x + config->gunOffset.x,
            gun->state.rotationCenter.y + config->gunOffset.y
        }
    );

    if (gun->resources.casingParticleEmitter) {
        gun->resources.casingParticleEmitter->position = Vec2_Add(
            gun->state.position, 
            Vec2_RotateAroundDegrees(
                casingPosition,
                (Vec2) {
                    gun->state.rotationCenter.x,
                    gun->state.rotationCenter.y 
                },
                gun->state.angle
            )
        );
    }
    
    if (gun->resources.muzzleFlashEmitter) {
        gun->resources.muzzleFlashEmitter->direction = Vec2_RotateDegrees(Vec2_Right, gun->state.angle);
        gun->resources.muzzleFlashEmitter->position = Vec2_Add(
            gun->state.position, 
            Vec2_RotateAroundDegrees(
                muzzlePosition,
                (Vec2) {
                    gun->state.rotationCenter.x,
                    gun->state.rotationCenter.y 
                },
                gun->state.angle
            )
        );
    }

    if (gun->resources.bulletPreset) {
        gun->resources.bulletPreset->direction = Vec2_RotateDegrees(Vec2_Right, gun->state.angle);
        gun->resources.bulletPreset->position = gun->resources.muzzleFlashEmitter->position;
    }
}

void Sentry_UpdateLazer(EnemyData* data) {
    SentryConfig* config = (SentryConfig*)data->config;
    GunData* gun = &config->gun;

    Vec2 currentLazerPosition = gun->resources.muzzleFlashEmitter->position;
    Vec2 targetDirection = gun->resources.muzzleFlashEmitter->direction;
    Collider lazer = (Collider) {
        .active = true,
        .hitbox = Vec2_ToSquareRect(currentLazerPosition, 1),
        .collidesWith = COLLISION_LAYER_ENVIRONMENT | 
                        COLLISION_LAYER_PLAYER
    };
    
    Collider_Register(&lazer, NULL);
    for (int i = 0; i < 1000; i++) {
        if (Vec2_AreEqual(targetDirection, Vec2_Zero)) {
            break;
        }
        ColliderCheckResult result;
        bool hitWall = false;
        Collider_Check(&lazer, &result);
        for (int j = 0; j < result.count; j++) {
            if (result.objects[j]->layer & COLLISION_LAYER_PLAYER) {
                if (config->state == SENTRY_STATE_SHOOTING) {
                    Player_TakeDamage(SentryData.stats.damage);
                }
            }
            if (result.objects[j]->layer & (COLLISION_LAYER_ENVIRONMENT)) {
                hitWall = true;
                break;
            }
        }
        if (hitWall) {
            break;
        }
        Vec2_Increment(&currentLazerPosition, targetDirection);
        lazer.hitbox = Vec2_ToSquareRect(currentLazerPosition, 1);
    }
    config->lazerStart = gun->resources.muzzleFlashEmitter->position;
    config->lazerEnd = currentLazerPosition;
    Collider_Reset(&lazer);
}

void Sentry_Update(EnemyData* data) {
    SentryConfig* config = (SentryConfig*)data->config;
    GunData* gun = &config->gun;

    float effectiveCooldown = data->stats.attackCooldown / data->state.tacticianBuff;

    if (data->state.currentHealth <= 0) {
        Animation_Destroy(gun->resources.animation);
        void* configToFree = config;
        data->config = NULL;
        free(configToFree);
        Enemy_HandleDeath(data);
        return;
    }
    
    config->timer += Time->deltaTimeSeconds;
    switch (config->state) {

    case SENTRY_STATE_IDLE:
        if (config->lazerWidth < 0) {
            gun->state.angle = atan2(
                player.state.position.y - gun->state.position.y,
                player.state.position.x - gun->state.position.x
            ) * 180 / M_PI;
        }

        if (config->timer >= config->idleTime) {
            config->idleTime = RandFloat(
                effectiveCooldown * 0.5f,
                effectiveCooldown * 1.5f
            );
            config->timer = 0;
            config->state = SENTRY_STATE_AIMING;
        }
        break;

    case SENTRY_STATE_AIMING:
        config->lazerWidth = 0; 

        if (config->timer >= config->aimTime) {
            config->timer = 0;
            config->state = SENTRY_STATE_SHOOTING;

            float angle = Vec2_AngleBetween(
                Vec2_Subtract(player.state.position, gun->state.position),
                gun->resources.muzzleFlashEmitter->direction
            );

            if (angle < 0) {
                config->shootAngleSpeed = abs(config->shootAngleSpeed);
            } else {
                config->shootAngleSpeed = -abs(config->shootAngleSpeed);
            }
        }
        break;

    case SENTRY_STATE_SHOOTING:
        config->lazerWidth = 5; // Set laser width to 5 when shooting

        gun->state.angle += config->shootAngleSpeed  * data->state.tacticianBuff * Time->deltaTimeSeconds;

        if (config->timer >= config->shootAngle / (abs(config->shootAngleSpeed) * data->state.tacticianBuff)) {
            config->timer = 0;
            config->state = SENTRY_STATE_IDLE;
        }
        break;
    }
    
    config->gun.state.position = data->state.position;
    data->state.flip = data->state.position.x > player.state.position.x ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    Sentry_UpdateGun(data);
    Sentry_UpdateLazer(data);

    Animation_Play(config->gun.resources.animation, "normal");
    config->lastPosition = data->state.position;
}

void Sentry_UpdateParticles() {
    if (!SentryBulletEmitter) return;
    ParticleEmitter_Update(SentryBulletEmitter);
    ParticleEmitter_Update(SentryMuzzleFlashEmitter);
    ParticleEmitter_Update(SentryCasingEmitter);
    ParticleEmitter_Update(SentryBulletFragmentsEmitter);

    for (int i = 0; i < SentryBulletEmitter->maxParticles; i++) {
        Particle* bullet = &SentryBulletEmitter->particles[i];
        if (!bullet->alive) continue;
        ColliderCheckResult result;
        Collider_Check(bullet->collider, &result);
        for (int j = 0; j < result.count; j++) {
            if (result.objects[j]->layer & COLLISION_LAYER_PLAYER) {
                Player_TakeDamage(SentryData.stats.damage);
            }
            if (result.objects[j]->layer & (COLLISION_LAYER_ENVIRONMENT | COLLISION_LAYER_PLAYER)) {
                SentryBulletFragmentsEmitter->position = bullet->position;
                SentryBulletFragmentsEmitter->direction = SentryBulletEmitter->direction;
                ParticleEmitter_ActivateOnce(SentryBulletFragmentsEmitter);
                Collider_Reset(bullet->collider);
                bullet->alive = false;
                break;
            }
        }
    }
}
