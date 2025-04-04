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

    if (!config->aiming) {
        // Calculate angle between gun -> mouse position
        gun->state.angle = atan2(
            player.state.position.y - gun->state.position.y,
            player.state.position.x - gun->state.position.x
        ) * 180 / M_PI;
    }

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
    Vec2 targetDirection = config->lazerDirection;
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
                if (config->shooting) {
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

    float effectiveCooldown = data->stats.attackCooldown * data->state.tacticianBuff;

    if (data->state.currentHealth <= 0) {
        Animation_Destroy(gun->resources.animation);
        void* configToFree = config;
        data->config = NULL;
        free(configToFree);
        Enemy_HandleDeath(data);
        return;
    }
        
    config->gun.state.position = data->state.position;
    data->state.flip = data->state.position.x > player.state.position.x ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    Sentry_UpdateGun(data);
    Sentry_UpdateLazer(data);

    // Sentry is stationary - no movement code
    data->state.direction = Vec2_Zero; // Always keep direction at zero
    
    config->shooting = false;
    if (!config->aiming) {
        config->shootTimer += Time->deltaTimeSeconds;
        if (config->shootTimer >= config->shootTime) {
            config->shootTimer = 0;
            config->shootTime = RandFloat(
                effectiveCooldown / 2, effectiveCooldown * 3 / 2
            );
            config->aiming = true;
            config->lazerDirection = Vec2_Normalize(
                Vec2_Subtract(
                    player.state.position, 
                    gun->resources.muzzleFlashEmitter->position
                )
            );
        }
    } else {
        config->lazerWidth = 0; 
        config->aimTimer += Time->deltaTimeSeconds;
        if (config->aimTimer >= config->aimTime - 0.3f) {
            config->lazerWidth = 5;
            config->lazerWidth = (5.0f * (1.0f - (config->aimTimer - 0.5f) / 0.3f));
            config->shooting = true;
        }
        if (config->aimTimer >= config->aimTime) {
            config->aiming = false;
            config->aimTimer = 0;
            Sound_Play_Effect(SOUND_VANTAGE_LASER);
        }
    }
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
