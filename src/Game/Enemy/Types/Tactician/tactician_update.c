/**
 * @file tactician_update.c
 * @brief Implements update logic for Tactician enemy type
 *
 * Contains the AI behavior and state updates for the Tactician enemy.
 *
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_tactician.h>
#include <player.h>
#include <time_system.h>
#include <random.h>
#include <circle.h>
#include <math.h>

/**
 * @brief Updates the gun position and orientation for the Tactician enemy
 * 
 * Calculates the gun position, rotation, and orientation based on the enemy's
 * position and the player's location. Also updates associated particle emitters
 * for muzzle flash and bullet casings.
 * 
 * @param data Pointer to the enemy data structure
 */
void Tactician_UpdateGun(EnemyData* data) {
    TacticianConfig* config = (TacticianConfig*)data->config;
    GunData* gun = &config->gun;
    
    // Tactician always aims directly at the player
    Gun_UpdatePosition(gun, data->state.position, player.state.position, config->gunOffset);
}

/**
 * @brief [PostUpdate] Updates the Tactician enemy's state and behavior
 * 
 * Handles the state machine for the Tactician enemy, which can buff nearby enemies
 * and fire bursts of shots at the player. The Tactician is designed to maintain
 * distance from the player while supporting other enemies.
 * 
 * @param data Pointer to the enemy data structure
 */
void Tactician_Update(EnemyData* data) {
    TacticianConfig* config = (TacticianConfig*)data->config;
    
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
    Tactician_UpdateGun(data);


    config->directionChangeTimer += Time->deltaTimeSeconds;
    if (config->directionChangeTimer >= config->directionChangeTime) {
        config->directionChangeTime = RandFloat(0.5f, 1.0f);
        config->directionChangeTimer = 0;
        
        // Prefer to maintain distance from player
        data->state.direction = Vec2_Normalize(Vec2_Subtract(player.state.position, data->state.position));
        float distFromPlayer = Vec2_Distance(data->state.position, player.state.position);

        if (distFromPlayer > 250) {
            data->state.direction = Vec2_RotateDegrees(data->state.direction, RandFloat(-45, 45));
        } else {
            data->state.direction = Vec2_RotateDegrees(data->state.direction, RandFloat(135, 225));
        }
    }

   
    if (config->state & TACTICIAN_STATE_SHOOTING) {
        config->burstTimer += Time->deltaTimeSeconds;
        if (config->burstTimer >= config->burstTime) {
            config->burstTimer = 0;
            config->currentBurstCount++;
            ParticleEmitter_ActivateOnce(config->gun.resources.muzzleFlashEmitter);
            ParticleEmitter_ActivateOnce(config->gun.resources.casingParticleEmitter);
            ParticleEmitter_ActivateOnce(config->gun.resources.bulletPreset);

            if (config->currentBurstCount >= config->maxBurstCount) {
                config->state &= ~TACTICIAN_STATE_SHOOTING;
                config->currentBurstCount = 0;
            }
        }
    } else {
        config->shootTimer += Time->deltaTimeSeconds;
        if (config->shootTimer >= config->shootTime) {
            config->shootTimer = 0;
            config->shootTime = RandFloat(
                data->stats.attackCooldown / 2, data->stats.attackCooldown * 3 / 2
            );
            config->currentBurstCount = 0;
            config->burstTimer = 0;
            config->state |= TACTICIAN_STATE_SHOOTING;
        }
    }

    if (config->state & TACTICIAN_STATE_COMMANDING) {
        config->commandTimer += Time->deltaTimeSeconds;
        if (config->commandTimer >= config->commandTime) {
            config->commandTime = RandFloat(3.0f, 5.0f);
            config->state &= ~TACTICIAN_STATE_COMMANDING;
        }
    } else {
        config->commandTimer += Time->deltaTimeSeconds;
        if (config->commandTimer >= config->commandTime) {
            config->commandTimer = 0;
            config->commandTime = 0.5f;
            config->state |= TACTICIAN_STATE_COMMANDING;

            for (int i = 0; i < ENEMY_MAX; i++) {
                if (enemies[i].state.isDead) continue;
                if (enemies[i].type == ENEMY_TYPE_TACTICIAN) continue;
                if (Vec2_Distance(data->state.position, enemies[i].state.position) > config->commandRadius) continue;

                enemies[i].state.tacticianBuff = config->buffStrength;
                enemies[i].state.tacticianBuffTimeLeft = 3.0f;
                SDL_Log("Tactician buff applied to enemy %d", i);
            }
        }
    }
    Animation_Play(config->gun.resources.animation, "idle");
    config->lastPosition = data->state.position;
}

/**
 * @brief Updates all particle emitters related to the Tactician enemy
 * 
 * Processes particle physics, collision detection, and damage calculation for 
 * bullets fired by the Tactician enemy. Also handles special visual effects for
 * the buff ability and bullet impacts.
 */
void Tactician_UpdateParticles() {
    if (!TacticianBulletEmitter) return;
    ParticleEmitter_Update(TacticianBulletEmitter);
    ParticleEmitter_Update(TacticianMuzzleFlashEmitter);
    ParticleEmitter_Update(TacticianCasingEmitter);
    ParticleEmitter_Update(TacticianBulletFragmentsEmitter);
    ParticleEmitter_Update(TacticianBuffEffectEmitter);

    for (int i = 0; i < TacticianBulletEmitter->maxParticles; i++) {
        Particle* bullet = &TacticianBulletEmitter->particles[i];
        if (!bullet->alive) continue;
        ColliderCheckResult result;
        Collider_Check(bullet->collider, &result);
        for (int j = 0; j < result.count; j++) {
            if (result.objects[j]->layer & COLLISION_LAYER_PLAYER) {
                Player_TakeDamage(TacticianData.stats.damage);
            }
            if (result.objects[j]->layer & COLLISION_LAYER_ENEMY) {
                EnemyData* enemy = (EnemyData*) result.objects[j]->owner;
                
                int totalDamage = TacticianData.stats.damage * player.stats.skillStat.crashOutCurrentMultipler;
                SDL_Log("Enemy took damage %d, remaining health %d", totalDamage, enemy->state.currentHealth);
                Enemy_TakeDamage(enemy, totalDamage);
                
                TacticianBulletFragmentsEmitter->position = bullet->position;
                TacticianBulletFragmentsEmitter->direction = TacticianBulletEmitter->direction;
                ParticleEmitter_ActivateOnce(TacticianBulletFragmentsEmitter);
                
                Collider_Reset(bullet->collider);
                bullet->alive = false;
                Vec2_Increment(&enemy->state.velocity, Vec2_Multiply(bullet->direction, 70));
                break;
            }
            if (result.objects[j]->layer & (COLLISION_LAYER_ENVIRONMENT | COLLISION_LAYER_PLAYER)) {
                TacticianBulletFragmentsEmitter->position = bullet->position;
                TacticianBulletFragmentsEmitter->direction = TacticianBulletEmitter->direction;
                ParticleEmitter_ActivateOnce(TacticianBulletFragmentsEmitter);
                Collider_Reset(bullet->collider);
                bullet->alive = false;
                break;
            }
        }
    }
}
