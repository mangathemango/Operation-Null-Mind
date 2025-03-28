/**
 * @file radius_render.c
 * @brief Renders Radius enemy type
 * 
 * Handles the visual presentation of Radius enemies.
 * 
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_radius.h>
#include <camera.h>
#include <app.h>
#include <circle.h>

/**
 * @brief [Render] Renders the Radius enemy
 * 
 * This function handles the rendering of the Radius enemy type.
 * 
 * @param data Pointer to the enemy data structure
 */
void Radius_Render(EnemyData* data) {
    RadiusConfig *config = (RadiusConfig*)data->config;
    if (!config) return;
    GunData *gun = &config->gun;

    // Optional: render orbit path when actively orbiting
    if (config->isOrbiting) {
        // Visual indicator could be implemented here
    }

    Animation_Render(gun->resources.animation, 
        Camera_WorldVecToScreen(gun->state.position), 
        gun->animData.spriteSize,
        gun->state.angle,
        &gun->state.rotationCenter,
        gun->state.flip);
}

void Radius_RenderParticles() {
    if (!RadiusBulletEmitter) return;
    ParticleEmitter_Render(RadiusBulletEmitter);
    ParticleEmitter_Render(RadiusMuzzleFlashEmitter);
    ParticleEmitter_Render(RadiusCasingEmitter);
    ParticleEmitter_Render(RadiusBulletFragmentsEmitter);
}
