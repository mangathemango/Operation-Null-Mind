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
#include <enemy_kamikaze.h>

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
    float effectiveCooldown = data->stats.attackCooldown / data->state.tacticianBuff;
    float effectiveProjectileSpeed = 500 * data->state.tacticianBuff;

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

    
    // Handle shooting - Radius always tries to maintain optimal distance for shooting
    config->shootTimer += Time->deltaTimeSeconds;
    if (config->shootTimer >= config->shootTime) {
        config->shootTimer = 0;
        config->shootTime = RandFloat(
            effectiveCooldown / 2, effectiveCooldown * 3 / 2
        );

        // Visual effects
        config->gun.resources.bulletPreset->particleSpeed = effectiveProjectileSpeed;
        ParticleEmitter_ActivateOnce(config->gun.resources.bulletPreset);
        ParticleEmitter_ActivateOnce(config->gun.resources.muzzleFlashEmitter);
        ParticleEmitter_ActivateOnce(config->gun.resources.casingParticleEmitter);
        Sound_Play_Effect(SOUND_GRENADE_LAUNCHER);
    }

    // Replace animation state handling with just "idle"
    if (data->stats.maxSpeed > 0) {
        Animation_Play(config->gun.resources.animation, "walking");
    } else {
        Animation_Play(config->gun.resources.animation, "idle");
    }
    config->lastPosition = data->state.position;
}

void Radius_UpdateParticles() {
    if (!RadiusBulletEmitter) return;
    
    for (int i = 0; i < RadiusBulletEmitter->maxParticles; i++) {
        Particle* bullet = &RadiusBulletEmitter->particles[i];
        if (!bullet->alive) continue;
        if (Collider_Check(bullet->collider, NULL))  {
            bullet->speed = 0;
            bullet->velocity = Vec2_Zero;
        }
        if (bullet->timeAlive + Time->deltaTimeSeconds >= bullet->maxLifeTime) {
            RadiusExplosionEmitter->position = bullet->position;
            ParticleEmitter_ActivateOnce(RadiusExplosionEmitter);
            Sound_Play_Effect(SOUND_EXPLOSION);
            if (IsRectOverlappingCircle(
                player.state.collider.hitbox,
                bullet->position, 
                RadiusConfigData.explosionRadius
                 
            )) {
                Player_TakeDamage(RadiusData.stats.damage);
            }
        }
    }

    ParticleEmitter_Update(RadiusBulletEmitter);
    ParticleEmitter_Update(RadiusMuzzleFlashEmitter);
    ParticleEmitter_Update(RadiusCasingEmitter);
    ParticleEmitter_Update(RadiusBulletFragmentsEmitter);
    ParticleEmitter_Update(RadiusExplosionEmitter);
}
