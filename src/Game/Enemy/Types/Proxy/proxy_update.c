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

    // Flip the gun's sprite if mouse is on the left side of the player
    // This also flips the gun's particles and muzzle flash particles.
    if (data->state.direction.x < 0) {
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

    // Calculate angle between gun -> mouse position
    gun->state.angle = atan2(
        Vec2_Subtract(player.state.position, data->state.position).y, 
        Vec2_Subtract(player.state.position, data->state.position).x
    ) * 180 / M_PI;

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

    config->gun.state.position = data->state.position;
    // Specific behaviors will be implemented later
    data->state.direction = Vec2_Normalize(Vec2_Subtract(player.state.position, data->state.position));

    
    if (Vec2_AreEqual(data->state.position, config->lastPosition)) {
        Animation_Play(config->gun.resources.animation, "idle");
    } else {
        Animation_Play(config->gun.resources.animation, "walkin");
    }
    config->lastPosition = data->state.position;

    Proxy_UpdateGun(data);
}
