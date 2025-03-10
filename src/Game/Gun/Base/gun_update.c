//? Written by Mango on 06/03/2025

#include <gun.h>
#include <player.h>
#include <input.h>
#include <math.h>

/*
*   [PostUpdate] Updates the gun's states, particles, and so on.
?   Because I'm lazy with the particle's position adjustment, every single bullet casing particle is placed
?   at the player's position - in the middle of the player's sprite. Therefore, every gun's center point
?   has to also be placed at the gun's ammo dispenser.
*/
void Gun_Update() {
    GunData* gun = player.state.currentGun;

    // Calculate angle between gun -> mouse position
    gun->state.angle = atan2(
        Vec2_Subtract(Input->mouse.position, player.state.position).y, 
        Vec2_Subtract(Input->mouse.position, player.state.position).x
    ) * 180 / M_PI;



    // Flip the gun's sprite if mouse is on the left side of the player
    if (Input->mouse.position.x < player.state.position.x) {
        gun->state.flip = SDL_FLIP_VERTICAL;
        gun->state.rotationCenter = (SDL_Point) {
            gun->config.gripPosition.x, 
            gun->animData.spriteSize.y - gun->config.gripPosition.y,
        };
    } else {
        gun->state.flip = SDL_FLIP_NONE;
        gun->state.rotationCenter = (SDL_Point) {
            gun->config.gripPosition.x,
            gun->config.gripPosition.y
        }; 
    }

    gun->state.position = Vec2_Subtract(
        player.state.position,
        (Vec2) {
            gun->state.rotationCenter.x,
            gun->state.rotationCenter.y - 5
        }
    );

    // Update casing particles
    if (gun->state.flip == SDL_FLIP_NONE) {
        gun->resources.casingParticleEmitter->direction = Vec2_RotateDegrees(Vec2_Right, gun->state.angle - 135);
    } else {
        gun->resources.casingParticleEmitter->direction = Vec2_RotateDegrees(Vec2_Right, gun->state.angle + 135);
    }
    
    Vec2 casingPosition = gun->config.ejectionPosition;
    if (gun->state.flip == SDL_FLIP_VERTICAL) {
        // Flip the position's y when gun is flipped
        casingPosition.y *= -1;
    }

    gun->resources.casingParticleEmitter->position = Vec2_Add(
        gun->state.position, 
        Vec2_RotateDegrees(
            casingPosition, 
            gun->state.angle
        ));
    ParticleEmitter_Update(gun->resources.casingParticleEmitter);

    // Get muzzle position
    Vec2 muzzlePosition = gun->config.muzzlePosition;
    if (gun->state.flip == SDL_FLIP_VERTICAL) {
        // Flip the position's y when gun is flipped
        muzzlePosition.y *= -1;
    }
    
    // Update muzzle flash particles
    gun->resources.muzzleFlashEmitter->direction = Vec2_RotateDegrees(Vec2_Right, gun->state.angle);
    gun->resources.muzzleFlashEmitter->position = Vec2_Add(
        gun->state.position, 
        Vec2_RotateDegrees(
            muzzlePosition, 
            gun->state.angle
        ));
    ParticleEmitter_Update(gun->resources.muzzleFlashEmitter);


    // Update gun's animations
    Gun_AnimationUpdate();
}