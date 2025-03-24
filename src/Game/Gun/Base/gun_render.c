/**
 * @file gun_render.c
 * @brief Handles rendering of weapons and weapon effects
 *
 * Manages the rendering of gun sprites, muzzle flashes,
 * and ejected casings with proper layering.
 *
 * @author Mango
 * @date 2025-03-05
 */

//? Written by Mango on 05/03/2025

#include <gun.h>
#include <input.h>
#include <player.h>

/**
 * @brief [Render] Renders the player's current gun and its corresponding particles
 * 
 * Draws the current weapon with proper rotation and flipping, and renders
 * muzzle flash and casing particles with correct layering based on weapon orientation.
 */
void Gun_Render() {
    GunData* gun = &player.state.currentGun;
    if (!gun) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Player gun data is missing");
        return;
    }
    if (!gun->resources.animation) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Gun animation resource is missing");
        return;
    }
    if (!gun->resources.muzzleFlashEmitter) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Muzzle flash particle emitter is missing");
        return;
    }
    if (!gun->resources.casingParticleEmitter) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Casing particle emitter is missing");
        return;
    }

    // Render muzzle flash particles
    ParticleEmitter_Render(gun->resources.muzzleFlashEmitter);
    SDL_Log("Rendering muzzle flash particles");

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