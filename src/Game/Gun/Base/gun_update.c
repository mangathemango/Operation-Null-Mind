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

    gun->state.position = Vec2_Subtract(
                            player.state.position, 
                            (Vec2) {24, 12} // This is the position of every gun's ammo dispenser.
                        );

    // I don't know why the rotationCenter it has to go up by {1, 1}, but it works
    gun->state.rotationCenter = (SDL_Point) {25, 13}; 
    
    // Flip the gun's sprite if mouse is on the left side of the player
    if (Input->mouse.position.x < player.state.position.x) {
        gun->state.flip = SDL_FLIP_VERTICAL;
    } else {
        gun->state.flip = SDL_FLIP_NONE;
    }

    // Update gun's animations
    Gun_AnimationUpdate();
    
    // Update casing particles
    if (gun->state.flip == SDL_FLIP_NONE) {
        gun->config.casingParticleEmitter->direction = Vec2_RotateDegrees(Vec2_Right, gun->state.angle - 135);
    } else {
        gun->config.casingParticleEmitter->direction = Vec2_RotateDegrees(Vec2_Right, gun->state.angle + 135);
    }
    
    gun->config.casingParticleEmitter->position = player.state.position;
    ParticleEmitter_Update(gun->config.casingParticleEmitter);

    // Get muzzle position
    Vec2 muzzlePosition = gun->config.muzzlePosition;
    if (gun->state.flip == SDL_FLIP_VERTICAL) {
        // Flip the position's y when gun is flipped
        muzzlePosition.y *= -1;
    }
    
    // Update muzzle flash particles
    gun->config.muzzleFlashEmitter->direction = Vec2_RotateDegrees(Vec2_Right, gun->state.angle);
    gun->config.muzzleFlashEmitter->position = Vec2_Add(
        player.state.position, 
        Vec2_RotateDegrees(
            muzzlePosition, 
            gun->state.angle
        ));
    ParticleEmitter_Update(gun->config.muzzleFlashEmitter);
}