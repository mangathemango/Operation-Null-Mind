/**
 * @file sabot_update.c
 * @brief Implements update logic for Sabot enemy type
 *
 * Contains the AI behavior and state updates for the Sabot enemy.
 *
 * @author Mango
 * @date 2025-03-21
 */

#include <enemy_sabot.h>
#include <player.h>
#include <time_system.h>
#include <random.h>
#include <circle.h>
#include <math.h>

/**
 * @brief Updates the gun position and orientation for the Sabot enemy
 * 
 * Calculates the gun position, rotation, and orientation based on the enemy's
 * position and the player's location. Also updates associated particle emitters
 * for muzzle flash and bullet casings.
 * 
 * @param data Pointer to the enemy data structure
 */
void Sabot_UpdateGun(EnemyData* data) {
    SabotConfig* config = (SabotConfig*)data->config;
    GunData* gun = &config->gun;
    
    // Sabot always aims directly at the player
    Gun_UpdatePosition(gun, data->state.position, player.state.position, config->gunOffset);
}

/**
 * @brief [PostUpdate] Updates the Sabot enemy's state and behavior
 * 
 * The Sabot enemy fires tracking projectiles that explode on impact.
 * This function handles movement, targeting, and shooting mechanics.
 * 
 * @param data Pointer to the enemy data structure
 */
void Sabot_Update(EnemyData* data) {
    SabotConfig* config = (SabotConfig*)data->config;
    
    float effectiveCooldown = data->stats.attackCooldown / data->state.tacticianBuff;
    float effectiveProjectileSpeed = 200 * data->state.tacticianBuff;

    if (data->state.currentHealth <= 0) {
        GunData* gun = &config->gun;
        Animation_Destroy(gun->resources.animation);
        void* configToFree = config;
        data->config = NULL;
        free(configToFree);
        Enemy_HandleDeath(data);
        return;
    }
        
    config->gun.state.position = data->state.position;
    data->state.flip = data->state.position.x > player.state.position.x ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    Sabot_UpdateGun(data);

    config->directionChangeTimer += Time->deltaTimeSeconds;
    if (config->directionChangeTimer >= config->directionChangeTime) {
        config->directionChangeTime = RandFloat(0.5f, 1.0f);
        config->directionChangeTimer = 0;
        data->state.direction = Vec2_Normalize(Vec2_Subtract(player.state.position, data->state.position));

        if (Vec2_Distance(player.state.position, data->state.position) > 150) {
            data->state.direction = Vec2_RotateDegrees(data->state.direction, RandFloat(-60, 60));
        } else {
            data->state.direction = Vec2_RotateDegrees(data->state.direction, RandFloat(90, 270));
        }
    }

    // Handle shooting - copied from Radius
    config->shootTimer += Time->deltaTimeSeconds;
    if (config->shootTimer >= config->shootTime) {
        config->shootTimer = 0;
        config->shootTime = RandFloat(
            effectiveCooldown / 2, effectiveCooldown * 3 / 2
        );

        // Visual effects
        config->gun.resources.bulletPreset->particleSpeed = effectiveProjectileSpeed;
        Sound_Play_Effect(SOUND_ROCKET_LAUNCH);
        ParticleEmitter_ActivateOnce(config->gun.resources.bulletPreset);
        ParticleEmitter_ActivateOnce(config->gun.resources.muzzleFlashEmitter);
        ParticleEmitter_ActivateOnce(config->gun.resources.casingParticleEmitter);
    }

    // Replace animation state handling with just "idle"
    if (data->stats.maxSpeed > 0) {
        Animation_Play(config->gun.resources.animation, "walking");
    } else {
        Animation_Play(config->gun.resources.animation, "idle");
    }
    config->lastPosition = data->state.position;
}

/**
 * @brief Updates all particle emitters related to the Sabot enemy
 * 
 * Handles the physics and tracking behavior of Sabot projectiles, including
 * homing behavior, explosion effects, and damage calculation. The Sabot's
 * projectiles are unique in that they track the player for a short time
 * after being fired.
 */
void Sabot_UpdateParticles() {
    if (!SabotBulletEmitter) return;
    
    for (int i = 0; i < SabotBulletEmitter->maxParticles; i++) {
        Particle* bullet = &SabotBulletEmitter->particles[i];
        if (!bullet->alive) continue;


        if (bullet->timeAlive <= 1 && (bullet->collider->layer & COLLISION_LAYER_PLAYER)) {
            Vec2 targetDirection = Vec2_Normalize(
                Vec2_Subtract(player.state.position, bullet->position)
            );
            float nextAngleRotation = Vec2_AngleBetween(
                bullet->direction, targetDirection
            ) * 5 * Time->deltaTimeSeconds;
            bullet->direction = Vec2_RotateDegrees(bullet->direction, nextAngleRotation);
        }
        
        if (Collider_Check(bullet->collider, NULL))  {
            SabotExplosionEmitter->position = bullet->position;
            ParticleEmitter_ActivateOnce(SabotExplosionEmitter);
            
            Sound_Play_Effect(SOUND_EXPLOSION);
            if (IsRectOverlappingCircle(
                player.state.collider.hitbox,
                bullet->position, 
                SabotConfigData.explosionRadius
            )) {
                Player_TakeDamage(SabotData.stats.damage);
            }
            bullet->alive = false;
        }
    }
    ParticleEmitter_Update(SabotBulletEmitter);
    ParticleEmitter_Update(SabotMuzzleFlashEmitter);
    ParticleEmitter_Update(SabotCasingEmitter);
    ParticleEmitter_Update(SabotBulletFragmentsEmitter);
    ParticleEmitter_Update(SabotExplosionEmitter);
}
