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

void Juggernaut_Update(EnemyData* data) {
    JuggernautConfig* config = (JuggernautConfig*)data->config;
    
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

    // Shooting logic is more aggressive when enraged
    config->shootTimer += Time->deltaTimeSeconds;
    if (config->shootTimer >= 0.1f) {
        config->shootTimer = 0;
        config->shootTime = RandFloat(
            data->stats.attackCooldown / 2, 
            data->stats.attackCooldown * 3 / 2
        );
        
        // Add slight spread for multiple bullets
        float angleOffset = 60;
        
        if (config->gun.resources.bulletPreset) {
            config->gun.resources.bulletPreset->direction = Vec2_RotateDegrees(
                Vec2_RotateDegrees(Vec2_Right, config->gun.state.angle),
                angleOffset
            );
            ParticleEmitter_ActivateOnce(config->gun.resources.bulletPreset);
            Sound_Play_Effect(SOUND_ENERGY_GUNSHOT);
        }
        
        
        ParticleEmitter_ActivateOnce(config->gun.resources.muzzleFlashEmitter);
        ParticleEmitter_ActivateOnce(config->gun.resources.casingParticleEmitter);
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
