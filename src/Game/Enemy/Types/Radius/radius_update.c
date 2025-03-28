/**
 * @file radius_update.c
 * @brief Implements update logic for Radius enemy type
 *
 * Contains the AI behavior and state updates for the Radius enemy.
 *
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_radius.h>
#include <player.h>
#include <time_system.h>
#include <random.h>
#include <circle.h>
#include <math.h>

void Radius_UpdateGun(EnemyData* data) {
    RadiusConfig* config = (RadiusConfig*)data->config;
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

void Radius_Update(EnemyData* data) {
    RadiusConfig* config = (RadiusConfig*)data->config;
    
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
    Radius_UpdateGun(data);

    float distToPlayer = Vec2_Distance(data->state.position, player.state.position);
    
    // Orbit behavior - key feature of the Radius enemy
    if (distToPlayer < config->orbitDistance * 1.2f && 
        distToPlayer > config->orbitDistance * 0.8f) {
        // Continue orbiting
        config->isOrbiting = true;
        
        // Update orbit angle
        config->orbitAngle += config->orbitSpeed * Time->deltaTimeSeconds;
        if (config->orbitAngle > 360.0f) config->orbitAngle -= 360.0f;
        
        // Calculate ideal orbit position
        Vec2 orbitCenter = player.state.position;
        Vec2 idealOrbitPos = {
            orbitCenter.x + cos(config->orbitAngle * M_PI / 180.0f) * config->orbitDistance,
            orbitCenter.y + sin(config->orbitAngle * M_PI / 180.0f) * config->orbitDistance
        };
        
        // Set direction toward ideal orbit position
        data->state.direction = Vec2_Normalize(Vec2_Subtract(idealOrbitPos, data->state.position));
    }
    else {
        // Not in orbit range - approach player or back off
        config->isOrbiting = false;
        
        if (distToPlayer > config->orbitDistance * 1.2f) {
            // Too far - approach
            data->state.direction = Vec2_Normalize(Vec2_Subtract(player.state.position, data->state.position));
        }
        else {
            // Too close - back away
            data->state.direction = Vec2_Normalize(Vec2_Subtract(data->state.position, player.state.position));
        }
    }
    
    // Handle shooting - Radius always tries to maintain optimal distance for shooting
    config->shootTimer += Time->deltaTimeSeconds;
    if (config->shootTimer >= config->shootTime && distToPlayer < config->orbitDistance * 1.5) {
        config->shootTimer = 0;
        config->shootTime = RandFloat(
            data->stats.attackCooldown / 2, data->stats.attackCooldown * 3 / 2
        );
        
        // Orbital enemies fire in patterns (spread shots)
        for (int i = 0; i < 3; i++) {
            float angleOffset = (i - 1) * config->shotSpreadRadius;
            
            // Adjust bullet emitter direction for spread shots
            if (config->gun.resources.bulletPreset) {
                config->gun.resources.bulletPreset->direction = Vec2_RotateDegrees(
                    Vec2_RotateDegrees(Vec2_Right, config->gun.state.angle),
                    angleOffset
                );
                
                ParticleEmitter_ActivateOnce(config->gun.resources.bulletPreset);
            }
        }
        
        // Visual effects
        ParticleEmitter_ActivateOnce(config->gun.resources.muzzleFlashEmitter);
        ParticleEmitter_ActivateOnce(config->gun.resources.casingParticleEmitter);
    }

    if (Vec2_AreEqual(data->state.position, config->lastPosition)) {
        Animation_Play(config->gun.resources.animation, "idle");
    } else {
        Animation_Play(config->gun.resources.animation, "walkin");
    }
    config->lastPosition = data->state.position;
}

void Radius_UpdateParticles() {
    if (!RadiusBulletEmitter) return;
    ParticleEmitter_Update(RadiusBulletEmitter);
    ParticleEmitter_Update(RadiusMuzzleFlashEmitter);
    ParticleEmitter_Update(RadiusCasingEmitter);
    ParticleEmitter_Update(RadiusBulletFragmentsEmitter);

    for (int i = 0; i < RadiusBulletEmitter->maxParticles; i++) {
        Particle* bullet = &RadiusBulletEmitter->particles[i];
        if (!bullet->alive) continue;
        ColliderCheckResult result;
        Collider_Check(bullet->collider, &result);
        for (int j = 0; j < result.count; j++) {
            if (result.objects[j]->layer & COLLISION_LAYER_PLAYER) {
                player.state.currentHealth -= RadiusData.stats.damage;
            }
            if (result.objects[j]->layer & (COLLISION_LAYER_ENVIRONMENT | COLLISION_LAYER_PLAYER)) {
                RadiusBulletFragmentsEmitter->position = bullet->position;
                RadiusBulletFragmentsEmitter->direction = RadiusBulletEmitter->direction;
                ParticleEmitter_ActivateOnce(RadiusBulletFragmentsEmitter);
                Collider_Reset(bullet->collider);
                bullet->alive = false;
                break;
            }
        }
    }
}
