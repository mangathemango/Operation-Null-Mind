/**
 * @file juggernaut_update.c
 * @brief Implements update logic for Juggernaut enemy type
 *
 * Contains the AI behavior and state updates for the Juggernaut enemy.
 *
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_juggernaut.h>
#include <player.h>
#include <time_system.h>
#include <random.h>
#include <circle.h>
#include <math.h>

void Juggernaut_UpdateGun(EnemyData* data) {
    JuggernautConfig* config = (JuggernautConfig*)data->config;
    GunData* gun = &config->gun;
    Vec2 muzzlePosition = gun->config.muzzlePosition;
    Vec2 casingPosition = gun->config.ejectionPosition;

    // Flip the gun's sprite if player is on the left side
    if (((int) gun->state.angle + 360) % 360 > 90 && ((int) gun->state.angle + 360) % 360 < 270) {
        gun->state.flip = SDL_FLIP_VERTICAL;
        data->state.flip = SDL_FLIP_HORIZONTAL;
        gun->state.rotationCenter = (SDL_Point) {
            gun->config.gripPosition.x, 
            gun->animData.spriteSize.y - gun->config.gripPosition.y,
        };
        muzzlePosition.y = gun->animData.spriteSize.y - muzzlePosition.y; 
        casingPosition.y = gun->animData.spriteSize.y - casingPosition.y;
        gun->resources.casingParticleEmitter->direction = Vec2_RotateDegrees(Vec2_Right, gun->state.angle + 135);
    } else {
        gun->state.flip = SDL_FLIP_NONE;
        data->state.flip = SDL_FLIP_NONE;
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

void Juggernaut_Update(EnemyData* data) {
    JuggernautConfig* config = (JuggernautConfig*)data->config;
    GunData* gun = &config->gun;
    float effectiveCooldown = 0.1f / data->state.tacticianBuff;
    float effectiveProjectileSpeed = 300 * data->state.tacticianBuff;

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

    Juggernaut_UpdateGun(data);
    config->timer += Time->deltaTimeSeconds;

    switch (config->state) {
        
    case JUGGERNAUT_STATE_WALKING:


        data->stats.maxSpeed = 80;
        // Calculate angle between gun -> player position
        gun->state.angle = atan2(
            player.state.position.y - gun->state.position.y,
            player.state.position.x - gun->state.position.x
        ) * 180 / M_PI;

        // Normal movement behavior
        config->directionChangeTimer += Time->deltaTimeSeconds;
        if (config->directionChangeTimer >= config->directionChangeTime) {
            config->directionChangeTime = RandFloat(0.5f, 1.0f);
            config->directionChangeTimer = 0;

            float distToPlayer = Vec2_Distance(player.state.position, data->state.position);
            // Normal movement logic
            if (distToPlayer > 150) {
                // Move toward player with some randomness
                data->state.direction = Vec2_Normalize(Vec2_Subtract(player.state.position, data->state.position));
                data->state.direction = Vec2_RotateDegrees(data->state.direction, RandFloat(-45, 45));
            } else {
                // Circle around at medium range
                data->state.direction = Vec2_Normalize(Vec2_Subtract(player.state.position, data->state.position));
                data->state.direction = Vec2_RotateDegrees(data->state.direction, RandFloat(45, 135));
            }
        }

        if (config->timer >= config->walkDuration) {
            config->timer = 0;
            config->state = JUGGERNAUT_STATE_CHARGING;
            config->walkDuration = RandFloat(2.0f, 4.0f);
        }
        break;

    case JUGGERNAUT_STATE_CHARGING:
        data->stats.maxSpeed = 0;
        if (config->timer >= config->chargeDuration) {
            config->timer = 0;
            config->shootTimer = 0;
            config->state = JUGGERNAUT_STATE_ENRAGED;
            config->enragedDuration = RandFloat(3.0f, 5.0f);
        }
        break;

    case JUGGERNAUT_STATE_ENRAGED:
        // Handle enraged state logic here
        gun->state.angle += config->spinSpeedDegrees * Time->deltaTimeSeconds;
        config->shootTimer += Time->deltaTimeSeconds;
        if (config->shootTimer >= effectiveCooldown) {
            config->shootTimer = 0;
            config->gun.resources.bulletPreset->particleSpeed = effectiveProjectileSpeed;
            ParticleEmitter_ActivateOnce(config->gun.resources.bulletPreset);
            ParticleEmitter_ActivateOnce(config->gun.resources.muzzleFlashEmitter);
            ParticleEmitter_ActivateOnce(config->gun.resources.casingParticleEmitter);
            Sound_Play_Effect(SOUND_ENERGY_GUNSHOT);
        }

        if (config->timer >= config->enragedDuration) {
            config->timer = 0;
            config->state = JUGGERNAUT_STATE_WALKING;
            config->walkDuration = RandFloat(2.0f, 4.0f);
        }
        break;

    default:
        break;
    }


    Animation_Play(config->gun.resources.animation, "idle");
    config->lastPosition = data->state.position;
}

void Juggernaut_UpdateParticles() {
    if (!JuggernautBulletEmitter) return;
    ParticleEmitter_Update(JuggernautBulletEmitter);
    ParticleEmitter_Update(JuggernautMuzzleFlashEmitter);
    ParticleEmitter_Update(JuggernautCasingEmitter);
    ParticleEmitter_Update(JuggernautBulletFragmentsEmitter);

    for (int i = 0; i < JuggernautBulletEmitter->maxParticles; i++) {
        Particle* bullet = &JuggernautBulletEmitter->particles[i];
        if (!bullet->alive) continue;
        ColliderCheckResult result;
        Collider_Check(bullet->collider, &result);
        for (int j = 0; j < result.count; j++) {
            if (result.objects[j]->layer & COLLISION_LAYER_PLAYER) {
                Player_TakeDamage(JuggernautData.stats.damage);
            }
            if(result.objects[j]->layer & COLLISION_LAYER_ENEMY)
            {
                //This will be removed when the whole parry system is implemented
                SDL_Log("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
                
                EnemyData* enemy = (EnemyData*) result.objects[j]->owner;
                
                int totalDamage = JuggernautData.stats.damage * player.stats.skillStat.crashOutCurrentMultipler;
                SDL_Log("Enemy took damage %d, remaining health %d",totalDamage, enemy->state.currentHealth);
                Enemy_TakeDamage(enemy, totalDamage);
                JuggernautBulletEmitter->position = bullet->position;
                JuggernautBulletFragmentsEmitter->direction = JuggernautBulletEmitter->direction;
                ParticleEmitter_ActivateOnce(JuggernautBulletFragmentsEmitter);
                Collider_Reset(bullet->collider);
                bullet->alive = false;
                Vec2_Increment(&enemy->state.velocity, Vec2_Multiply(bullet->direction, 70)); 
                break;
            }
            if (result.objects[j]->layer & (COLLISION_LAYER_ENVIRONMENT | COLLISION_LAYER_PLAYER)) {
                JuggernautBulletFragmentsEmitter->position = bullet->position;
                JuggernautBulletFragmentsEmitter->direction = JuggernautBulletEmitter->direction;
                ParticleEmitter_ActivateOnce(JuggernautBulletFragmentsEmitter);
                Collider_Reset(bullet->collider);
                bullet->alive = false;
                break;
            }
        }
    }
}
