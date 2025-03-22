//? Written by Mango on 05/03/2025

#include <gun.h>
#include <input.h>
#include <player.h>

/**
 * @brief [Render] Renders the player's current gun and its corresponding particles
 */
void Gun_Render() {
    GunData* gun = player.state.currentGun;

    // Render muzzle flash particles
    ParticleEmitter_Render(gun->resources.muzzleFlashEmitter);
    
    // (According to Darrel) If the gun is flipped, the gun casing particles go BEHIND the gun 
    // Therefore, the casing particles will be rendered first...
    if (gun->state.flip == SDL_FLIP_VERTICAL) {
        ParticleEmitter_Render(gun->resources.casingParticleEmitter);
    }

    // .. and then we render the gun...
    Animation_Render(gun->resources.animation, 
                    Camera_WorldVecToScreen(gun->state.position), 
                    gun->animData.spriteSize,
                    gun->state.angle,
                    &gun->state.rotationCenter,
                    gun->state.flip);
    
    // ...But otherwise, the particles go in FRONT of the gun instead. 
    // In other words, it gets rendered AFTER the gun.
    if (gun->state.flip == SDL_FLIP_NONE) {
        ParticleEmitter_Render(gun->resources.casingParticleEmitter);
    }   
}