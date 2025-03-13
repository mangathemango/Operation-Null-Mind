//? Written by Mango on 06/03/2025

#include <gun.h>
#include <player.h>
#include <input.h>
#include <math.h>

/*
*   [PostUpdate] Updates the gun's states, particles, and so on.
?   This part is really confusing, but it's basically updating the gun's position, angle, and particles.
!   I don't like how the gun's position is calculated, but it works.
*/
void Gun_Update() {
    GunData* gun = player.state.currentGun;
    Vec2 muzzlePosition = gun->config.muzzlePosition;
    Vec2 casingPosition = gun->config.ejectionPosition;

    Vec2 mouseWorldPosition = Camera_ScreenToWorld(Input->mouse.position);

    // Flip the gun's sprite if mouse is on the left side of the player
    // This also flips the gun's particles and muzzle flash particles.
    if (mouseWorldPosition.x < player.state.position.x) {
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
        Vec2_Subtract(mouseWorldPosition, player.state.position).y, 
        Vec2_Subtract(mouseWorldPosition, player.state.position).x
    ) * 180 / M_PI;

    // Update gun's position
    gun->state.position = Vec2_Subtract(
        player.state.position,
        (Vec2) {
            gun->state.rotationCenter.x,
            gun->state.rotationCenter.y - 5 // This -5 moves the gun down a bit for aesthetics.
        }
    );

    // Update casing particles
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
    
    // Update muzzle flash particles
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

    // Update gun's animations
    Gun_AnimationUpdate();
}