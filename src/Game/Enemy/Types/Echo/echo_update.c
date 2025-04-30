/**
 * @file echo_update.c
 * @brief Implements update logic for Echo enemy type
 *
 * Contains the AI behavior and state updates for the Echo enemy.
 *
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_echo.h>
#include <player.h>
#include <time_system.h>
#include <random.h>
#include <circle.h>
#include <math.h>

/**
 * @brief [PostUpdate] Updates the Echo enemy's state
 * 
 * This function is called each frame to update the Echo enemy's behavior.
 * The Echo enemy mimics player movements with a delay.
 * 
 * @param data Pointer to the enemy data structure
 */
void Echo_Update(EnemyData* data) {
    EchoConfig* config = (EchoConfig*)data->config;
    
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
    Echo_UpdateGun(data);
    

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
    
    switch (config->state) {
    
    case ECHO_STATE_WALKING:
        config->shootTimer += Time->deltaTimeSeconds;
        if (config->shootTimer >= config->shootTime) {
            config->shootTimer = 0;
            config->shootTime = RandFloat(
                effectiveCooldown / 2, effectiveCooldown * 3 / 2
            );
            config->state = ECHO_STATE_BURSTING;
        }
        break;
    case ECHO_STATE_BURSTING:
        config->burstTimer += Time->deltaTimeSeconds;
        if (config->burstTimer >= config->burstTime) {
            config->gun.resources.bulletPreset->particleSpeed = effectiveProjectileSpeed;
            ParticleEmitter_ActivateOnce(config->gun.resources.muzzleFlashEmitter);
            ParticleEmitter_ActivateOnce(config->gun.resources.casingParticleEmitter);
            ParticleEmitter_ActivateOnce(config->gun.resources.bulletPreset);
            Sound_Play_Effect(SOUND_ENERGY_GUNSHOT);
            config->burstCount++;
            config->burstTimer = 0;
        }

        if (config->burstCount >= config->burstMaxCount) {
            config->burstCount = 0;
            config->state = ECHO_STATE_WALKING;
        }
        break;
    }


    if (data->stats.maxSpeed > 0) {
        Animation_Play(data->resources.animation, "walking");
    } else {
        Animation_Play(data->resources.animation, "idle");
    }
    
    config->lastPosition = data->state.position;
}

void Echo_UpdateGun(EnemyData* data) {
    EchoConfig* config = (EchoConfig*)data->config;
    GunData* gun = &config->gun;
    Vec2 muzzlePosition = gun->config.muzzlePosition;
    Vec2 casingPosition = gun->config.ejectionPosition;

    // Calculate angle between gun -> player position
    gun->state.angle = atan2(
        player.state.position.y - gun->state.position.y,
        player.state.position.x - gun->state.position.x
    ) * 180 / M_PI;

    // Flip the gun's sprite if player is on the left side
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


void Echo_UpdateParticles() {
    if (!EchoBulletEmitter) return;
    ParticleEmitter_Update(EchoBulletEmitter);
    ParticleEmitter_Update(EchoMuzzleFlashEmitter);
    ParticleEmitter_Update(EchoCasingEmitter);
    ParticleEmitter_Update(EchoBulletFragmentsEmitter);

    for (int i = 0; i < EchoBulletEmitter->maxParticles; i++) {
        Particle* bullet = &EchoBulletEmitter->particles[i];
        if (!bullet->alive) continue;
        ColliderCheckResult result;
        Collider_Check(bullet->collider, &result);
        for (int j = 0; j < result.count; j++) {
            if (result.objects[j]->layer & COLLISION_LAYER_PLAYER) {
                Player_TakeDamage(EchoData.stats.damage);
            }
            if(result.objects[j]->layer & COLLISION_LAYER_ENEMY)
            {
                EnemyData* enemy = (EnemyData*) result.objects[j]->owner;
                
                int totalDamage = EchoData.stats.damage * player.stats.skillStat.crashOutCurrentMultipler;
                Enemy_TakeDamage(enemy, totalDamage);
                EchoBulletFragmentsEmitter->position = bullet->position;
                EchoBulletFragmentsEmitter->direction = EchoBulletEmitter->direction;
                ParticleEmitter_ActivateOnce(EchoBulletFragmentsEmitter);
                Collider_Reset(bullet->collider);
                bullet->alive = false;
                Vec2_Increment(&enemy->state.velocity, Vec2_Multiply(bullet->direction, 70)); 
                break;
            }
            if (result.objects[j]->layer & (COLLISION_LAYER_ENVIRONMENT | COLLISION_LAYER_PLAYER)) {
                EchoBulletFragmentsEmitter->position = bullet->position;
                EchoBulletFragmentsEmitter->direction = EchoBulletEmitter->direction;
                ParticleEmitter_ActivateOnce(EchoBulletFragmentsEmitter);
                Collider_Reset(bullet->collider);
                bullet->alive = false;
                break;
            }
        }
    }
}