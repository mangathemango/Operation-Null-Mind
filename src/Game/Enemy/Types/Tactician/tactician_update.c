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

void Tactician_UpdateGun(EnemyData* data) {
    TacticianConfig* config = (TacticianConfig*)data->config;
    GunData* gun = &config->gun;
    Vec2 muzzlePosition = gun->config.muzzlePosition;
    Vec2 casingPosition = gun->config.ejectionPosition;

    // Calculate angle between gun -> mouse position
    gun->state.angle = atan2(
        player.state.position.y - gun->state.position.y,
        player.state.position.x - gun->state.position.x
    ) * 180 / M_PI;

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


    Animation_Play(config->gun.resources.animation, "idle");
    config->lastPosition = data->state.position;
}

void Tactician_UpdateParticles() {
    if (!TacticianBulletEmitter) return;
    ParticleEmitter_Update(TacticianBulletEmitter);
    ParticleEmitter_Update(TacticianMuzzleFlashEmitter);
    ParticleEmitter_Update(TacticianCasingEmitter);
    ParticleEmitter_Update(TacticianBulletFragmentsEmitter);

    for (int i = 0; i < TacticianBulletEmitter->maxParticles; i++) {
        Particle* bullet = &TacticianBulletEmitter->particles[i];
        if (!bullet->alive) continue;
        ColliderCheckResult result;
        Collider_Check(bullet->collider, &result);
        for (int j = 0; j < result.count; j++) {
            if (result.objects[j]->layer & COLLISION_LAYER_PLAYER) {
                Player_TakeDamage(TacticianData.stats.damage);
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
