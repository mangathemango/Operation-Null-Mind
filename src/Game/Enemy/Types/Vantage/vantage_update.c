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

/**
 * @brief Updates the gun position and orientation for the Vantage enemy
 * 
 * Calculates the gun position, rotation, and orientation based on the enemy's
 * position and the player's location. Also updates associated particle emitters
 * for muzzle flash and bullet casings.
 * 
 * @param data Pointer to the enemy data structure
 */
void Vantage_UpdateGun(EnemyData* data) {
    VantageConfig* config = (VantageConfig*)data->config;
    GunData* gun = &config->gun;
    
    // Use the generalized gun position update function if not aiming
    // For Vantage, we use the player position as the target if not in aiming state
    if (!config->aiming) {
        Gun_UpdatePosition(gun, data->state.position, player.state.position, config->gunOffset);
    } else {
        // When aiming, we only update the position of the gun but not the angle
        Vec2 targetPos;
        // Calculate a point in the aiming direction for aiming mode
        targetPos.x = data->state.position.x + cosf(gun->state.angle * M_PI / 180.0f) * 100.0f;
        targetPos.y = data->state.position.y + sinf(gun->state.angle * M_PI / 180.0f) * 100.0f;
        
        Gun_UpdatePosition(gun, data->state.position, targetPos, config->gunOffset);
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
    if (data->stats.maxSpeed > 0) {
        Animation_Play(data->resources.animation, "walking");
    } else {
        Animation_Play(data->resources.animation, "idle");
    }
    config->lastPosition = data->state.position;
}

/**
 * @brief Updates all particle emitters related to the Vantage enemy
 * 
 * Handles particle physics, collision detection, and damage calculation for 
 * bullets fired by the Vantage enemy. This function should be called once per frame
 * to properly update and render all Vantage-specific particles.
 */
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

/**
 * @brief Updates the laser targeting system for the Vantage enemy
 * 
 * Calculates the laser beam's path from the gun to the first obstacle or player,
 * handling collision detection and damage application. The laser is used for both
 * visualization (showing where the Vantage is aiming) and for dealing damage when
 * in shooting state.
 *
 * @param data Pointer to the enemy data structure
 */
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