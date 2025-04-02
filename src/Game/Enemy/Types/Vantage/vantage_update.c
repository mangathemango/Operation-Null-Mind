/**
 * @file vantage_update.c
 * @brief Implements update logic for Vantage enemy type
 *
 * Contains the AI behavior and state updates for the Vantage enemy.
 *
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_vantage.h>
#include <player.h>
#include <time_system.h>
#include <random.h>
#include <circle.h>
#include <math.h>

void Vantage_UpdateGun(EnemyData* data) {
    VantageConfig* config = (VantageConfig*)data->config;
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

/**
 * @brief [PostUpdate] Updates the Vantage enemy's state
 * 
 * This function is called each frame to update the Vantage enemy's behavior.
 * The Vantage enemy is a long-range sniper that can detect the player from far away.
 * 
 * @param data Pointer to the enemy data structure
 */
void Vantage_Update(EnemyData* data) {
    VantageConfig* config = (VantageConfig*)data->config;
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
    Vantage_UpdateGun(data);
    Vantage_UpdateLazer(data);

    config->shooting = false;
    if (!config->aiming) {
        data->stats.maxSpeed = 200;
        config->directionChangeTimer += Time->deltaTimeSeconds;
        if (config->directionChangeTimer >= config->directionChangeTime) {
            config->directionChangeTime = RandFloat(0.5f, 1.0f);
            config->directionChangeTimer = 0;

            // Circle around the player
            float distToPlayer = Vec2_Distance(data->state.position, player.state.position);
            if (distToPlayer > 200) {
                data->state.direction = Vec2_Normalize(Vec2_Subtract(player.state.position, data->state.position));
                data->state.direction = Vec2_RotateDegrees(data->state.direction, RandFloat(-60, 60));
            } else {
                data->state.direction = Vec2_Normalize(Vec2_Subtract(player.state.position, data->state.position));
                data->state.direction = Vec2_RotateDegrees(data->state.direction, RandFloat(90, 270));
            }
        }

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
        data->stats.maxSpeed = 0;
        config->aimTimer += Time->deltaTimeSeconds;
        if (config->aimTimer >= config->aimTime - 0.3f) {
            config->lazerWidth = 5;
            config->lazerWidth = (5.0f * (1.0f - (config->aimTimer - 0.5f) / 0.3f)); // Gradually increase width
            config->shooting = true;
        }
        if (config->aimTimer >= config->aimTime) {
            config->aiming = false;
            config->aimTimer = 0;
            Sound_Play_Effect(SOUND_VANTAGE_LASER);
        }
    }
    // Replace animation state handling with just "idle"
    Animation_Play(config->gun.resources.animation, "idle");
    config->lastPosition = data->state.position;
}

void Vantage_UpdateParticles() {
    if (!VantageBulletEmitter) return;
    ParticleEmitter_Update(VantageBulletEmitter);
    ParticleEmitter_Update(VantageMuzzleFlashEmitter);
    ParticleEmitter_Update(VantageCasingEmitter);
    ParticleEmitter_Update(VantageBulletFragmentsEmitter);

    for (int i = 0; i < VantageBulletEmitter->maxParticles; i++) {
        Particle* bullet = &VantageBulletEmitter->particles[i];
        if (!bullet->alive) continue;
        ColliderCheckResult result;
        Collider_Check(bullet->collider, &result);
        for (int j = 0; j < result.count; j++) {
            if (result.objects[j]->layer & COLLISION_LAYER_PLAYER) {
                player.state.currentHealth -= VantageData.stats.damage;
            }
            if (result.objects[j]->layer & (COLLISION_LAYER_ENVIRONMENT | COLLISION_LAYER_PLAYER)) {
                VantageBulletFragmentsEmitter->position = bullet->position;
                VantageBulletFragmentsEmitter->direction = VantageBulletEmitter->direction;
                ParticleEmitter_ActivateOnce(VantageBulletFragmentsEmitter);
                Collider_Reset(bullet->collider);
                bullet->alive = false;
                break;
            }
        }
    }
}

void Vantage_UpdateLazer(EnemyData* data) {
    VantageConfig* config = (VantageConfig*)data->config;
    GunData* gun = &config->gun;

    Vec2 currentLazerPosition = gun->resources.muzzleFlashEmitter->position;
    Vec2 targetDirection = config->lazerDirection;
    Collider lazer = (Collider) {
        .active = true,
        .hitbox = Vec2_ToSquareRect(currentLazerPosition, 1
        ),
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
                    Player_TakeDamage(VantageData.stats.damage);
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