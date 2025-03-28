/**
 * @file proxy_update.c
 * @brief Implements update logic for Proxy enemy type
 *
 * Contains the AI behavior and state updates for the Proxy enemy.
 *
 * @author Mango
 * @date 2025-03-20
 */

#include <enemy_proxy.h>
#include <player.h>
#include <time_system.h>
#include <random.h>
#include <circle.h>
#include <math.h>


void Proxy_UpdateGun(EnemyData* data) {
    ProxyConfig* config = (ProxyConfig*)data->config;
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
            gun->state.rotationCenter.y + config->gunOffset.y // This -5 moves the gun down a bit for aesthetics.
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
        ParticleEmitter_Update(gun->resources.casingParticleEmitter);
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
        ParticleEmitter_Update(gun->resources.muzzleFlashEmitter);
    }
}

/**
 * @brief [PostUpdate] Updates the Proxy enemy's state
 * 
 * This function is called each frame to update the Proxy enemy's behavior.
 * The Proxy enemy deploys at a position and can act as a decoy or amplifier
 * for other enemies.
 * 
 * @param data Pointer to the enemy data structure
 */
void Proxy_Update(EnemyData* data) {
    ProxyConfig* config = (ProxyConfig*)data->config;
    
    if (data->state.currentHealth <= 0) {
        GunData* gun = &config->gun;
        
        // Now destroy resources
        Animation_Destroy(gun->resources.animation);
        ParticleEmitter_DestroyEmitter(gun->resources.bulletPreset);
        ParticleEmitter_DestroyEmitter(gun->resources.casingParticleEmitter);
        ParticleEmitter_DestroyEmitter(gun->resources.muzzleFlashEmitter);
        ParticleEmitter_DestroyEmitter(gun->resources.bulletFragmentEmitter);

        // Set config to NULL in data before freeing it
        void* configToFree = config;
        data->config = NULL;
        
        // Now free memory and handle death
        free(configToFree);
        Enemy_HandleDeath(data);
        return;
    }

    config->gun.state.position = data->state.position;
    
    config->directionChangeTimer += Time->deltaTimeSeconds;
    if (config->directionChangeTimer >= config->directionChangeTime) {
        config->directionChangeTime = RandFloat(0.5f, 1.0f);
        config->directionChangeTimer = 0;
        data->state.direction = Vec2_Normalize(Vec2_Subtract(player.state.position, data->state.position));

        if (Vec2_Distance(player.state.position, data->state.position) > 150) {
            data->state.direction = Vec2_RotateDegrees(data->state.direction, RandFloat(-45, 45));
        } else {
            data->state.direction = Vec2_RotateDegrees(data->state.direction, RandFloat(90, 270));
        }
    }

    if (Vec2_AreEqual(data->state.position, config->lastPosition)) {
        Animation_Play(config->gun.resources.animation, "idle");
    } else {
        Animation_Play(config->gun.resources.animation, "walkin");
    }
    config->lastPosition = data->state.position;
    data->state.flip = data->state.position.x > player.state.position.x ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    Proxy_UpdateGun(data);
}
