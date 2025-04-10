/**
 * @file gun_position.c
 * @brief Implements a generalized gun positioning system for all entity types
 *
 * Provides a shared function to update gun position, rotation, and particle emitters
 * for any entity that uses a gun (player or enemies).
 *
 * @author Mango
 * @date 2025-04-05
 */

#include <gun.h>
#include <math.h>

/**
 * @brief Updates gun position, orientation and associated particle emitters
 * 
 * A generalized function to handle gun positioning, orientation, and particle emitter
 * updates for any entity (player or enemy) that uses a gun. This eliminates duplicate code
 * across different enemy types.
 * 
 * @param gun Pointer to the gun data structure
 * @param ownerPosition Position of the entity that owns the gun
 * @param targetPosition Position to aim at (usually player position)
 * @param gunOffset Additional offset from owner position
 */
void Gun_UpdatePosition(GunData* gun, Vec2 ownerPosition, Vec2 targetPosition, Vec2 gunOffset){
    if(!gun) return;
    
    Vec2 muzzlePosition = gun->config.muzzlePosition;
    Vec2 casingPosition = gun->config.ejectionPosition;

    // Calculate angle between gun -> target position
    gun->state.angle = atan2(
        targetPosition.y - ownerPosition.y,
        targetPosition.x - ownerPosition.x
    ) * 180 / M_PI;

    // Flip the gun's sprite if target is on the left side
    if(targetPosition.x < ownerPosition.x){
        gun->state.flip = SDL_FLIP_VERTICAL;
        gun->state.rotationCenter = (SDL_Point){
            gun->config.gripPosition.x, 
            gun->animData.spriteSize.y - gun->config.gripPosition.y,
        };
        muzzlePosition.y = gun->animData.spriteSize.y - muzzlePosition.y; 
        casingPosition.y = gun->animData.spriteSize.y - casingPosition.y;
        
        if(gun->resources.casingParticleEmitter){
            gun->resources.casingParticleEmitter->direction = Vec2_RotateDegrees(Vec2_Right, gun->state.angle + 135);
        }
    }else{
        gun->state.flip = SDL_FLIP_NONE;
        gun->state.rotationCenter = (SDL_Point){
            gun->config.gripPosition.x,
            gun->config.gripPosition.y
        }; 
        
        if(gun->resources.casingParticleEmitter){
            gun->resources.casingParticleEmitter->direction = Vec2_RotateDegrees(Vec2_Right, gun->state.angle - 135);
        }
    }

    // Update gun's position
    gun->state.position = Vec2_Subtract(
        ownerPosition,
        (Vec2){
            gun->state.rotationCenter.x + gunOffset.x,
            gun->state.rotationCenter.y + gunOffset.y
        }
    );

    // Update casing emitter position
    if(gun->resources.casingParticleEmitter){
        gun->resources.casingParticleEmitter->position = Vec2_Add(
            gun->state.position, 
            Vec2_RotateAroundDegrees(
                casingPosition,
                (Vec2){
                    gun->state.rotationCenter.x,
                    gun->state.rotationCenter.y 
                },
                gun->state.angle
            )
        );
    }
    
    // Update muzzle flash emitter position
    if(gun->resources.muzzleFlashEmitter){
        gun->resources.muzzleFlashEmitter->direction = Vec2_RotateDegrees(Vec2_Right, gun->state.angle);
        gun->resources.muzzleFlashEmitter->position = Vec2_Add(
            gun->state.position, 
            Vec2_RotateAroundDegrees(
                muzzlePosition,
                (Vec2){
                    gun->state.rotationCenter.x,
                    gun->state.rotationCenter.y 
                },
                gun->state.angle
            )
        );
    }

    // Update bullet preset position
    if(gun->resources.bulletPreset){
        gun->resources.bulletPreset->direction = Vec2_RotateDegrees(Vec2_Right, gun->state.angle);
        gun->resources.bulletPreset->position = gun->resources.muzzleFlashEmitter 
            ? gun->resources.muzzleFlashEmitter->position 
            : gun->state.position;
    }
}
