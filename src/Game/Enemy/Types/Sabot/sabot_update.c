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

void Sabot_UpdateGun(EnemyData* data) {
    SabotConfig* config = (SabotConfig*)data->config;
    GunData* gun = &config->gun;
    Vec2 muzzlePosition = gun->config.muzzlePosition;
    Vec2 casingPosition = gun->config.ejectionPosition;

    // Calculate angle between gun -> mouse position
    gun->state.angle = atan2(
        player.state.position.y - gun->state.position.y,
        player.state.position.x - gun->state.position.x
    ) * 180 / M_PI;

    // Flip the gun's sprite if mouse is on the left side of the player
    // This also flips the gun's particles and muzzle flash particles.
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

/**
 * @brief [PostUpdate] Updates the Sabot enemy's state
 * 
 * This function is called each frame to update the Sabot enemy's behavior.
 * 
 * @param data Pointer to the enemy data structure
 */
void Sabot_Update(EnemyData* data) {
    SabotConfig* config = (SabotConfig*)data->config;
    
    if (data->state.currentHealth <= 0) {
        GunData* gun = &config->gun;
        
        // Now destroy resources
        Animation_Destroy(gun->resources.animation);

        // Set config to NULL in data before freeing it
        void* configToFree = config;
        data->config = NULL;
        
        // Now free memory and handle death
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

    // Replace animation state handling with just "idle"
    Animation_Play(config->gun.resources.animation, "idle");
    config->lastPosition = data->state.position;
}

void Sabot_UpdateParticles() {
    if (!SabotBulletEmitter) return;
    ParticleEmitter_Update(SabotBulletEmitter);
    ParticleEmitter_Update(SabotMuzzleFlashEmitter);
    ParticleEmitter_Update(SabotCasingEmitter);
    ParticleEmitter_Update(SabotBulletFragmentsEmitter);

    for (int i = 0; i < SabotBulletEmitter->maxParticles; i++) {
        Particle* bullet = &SabotBulletEmitter->particles[i];
        if (!bullet->alive) continue;
        ColliderCheckResult result;
        Collider_Check(bullet->collider, &result);
        for (int j = 0; j < result.count; j++) {
            if (result.objects[j]->layer & COLLISION_LAYER_PLAYER) {
                player.state.currentHealth -= SabotData.stats.damage;
            }
            if (result.objects[j]->layer & (COLLISION_LAYER_ENVIRONMENT | COLLISION_LAYER_PLAYER)) {
                SabotBulletFragmentsEmitter->position = bullet->position;
                SabotBulletFragmentsEmitter->direction = SabotBulletEmitter->direction;
                ParticleEmitter_ActivateOnce(SabotBulletFragmentsEmitter);
                Collider_Reset(bullet->collider);
                bullet->alive = false;
                break;
            }
        }
    }
}

void Sabot_RenderParticles() {
    if (!SabotBulletEmitter) return;
    ParticleEmitter_Render(SabotBulletEmitter);
    ParticleEmitter_Render(SabotMuzzleFlashEmitter);
    ParticleEmitter_Render(SabotCasingEmitter);
    ParticleEmitter_Render(SabotBulletFragmentsEmitter);
}
