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

void Sentry_Update(EnemyData* data) {
    SentryConfig* config = (SentryConfig*)data->config;
    
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
    Sentry_UpdateGun(data);

    // Check if player is within guard radius
    float distanceToPlayer = Vec2_Distance(data->state.position, player.state.position);
    
    if (distanceToPlayer < config->guardRadius) {
        // Increase alert level as player stays in range
        config->alertLevel += Time->deltaTimeSeconds * 0.5f;
        
        if (config->alertLevel >= config->alertThreshold) {
            config->isAlerted = true;
            
            // When alerted, shoot at player
            config->shootTimer += Time->deltaTimeSeconds;
            if (config->shootTimer >= config->shootTime) {
                config->shootTimer = 0;
                config->shootTime = RandFloat(
                    data->stats.attackCooldown / 2, data->stats.attackCooldown * 3 / 2
                );
                ParticleEmitter_ActivateOnce(config->gun.resources.muzzleFlashEmitter);
                ParticleEmitter_ActivateOnce(config->gun.resources.casingParticleEmitter);
                ParticleEmitter_ActivateOnce(config->gun.resources.bulletPreset);
            }
            
            // Sentry doesn't move when alerted, just aims
            data->state.direction = Vec2_Zero;
        }
        else {
            // Not yet alerted, just patrol
            data->state.direction = Vec2_Zero; // Sentries are stationary
        }
    }
    else {
        // Player outside guard radius, decrease alert level
        config->alertLevel -= Time->deltaTimeSeconds * 0.2f;
        if (config->alertLevel < 0) config->alertLevel = 0;
        
        if (config->alertLevel < config->alertThreshold) {
            config->isAlerted = false;
        }
        
        // When not alerted, occasionally look around
        config->directionChangeTimer += Time->deltaTimeSeconds;
        if (config->directionChangeTimer >= config->directionChangeTime) {
            config->directionChangeTime = RandFloat(2.0f, 4.0f);
            config->directionChangeTimer = 0;
            // Just change gun angle, not position
        }
    }

    Animation_Play(config->gun.resources.animation, "idle");
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
                player.state.currentHealth -= SentryData.stats.damage;
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
