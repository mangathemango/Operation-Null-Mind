/**
 * @file juggernaut_render.c
 * @brief Renders Juggernaut enemy type
 *
 * Handles the visual presentation of Juggernaut enemies.
 * 
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_juggernaut.h>
#include <camera.h>
#include <app.h>
#include <circle.h>

/**
 * @brief [Render] Renders the Juggernaut enemy
 * 
 * This function handles the rendering of the Juggernaut enemy type.
 * 
 * @param data Pointer to the enemy data structure
 */
void Juggernaut_Render(EnemyData* data) {
    JuggernautConfig *config = (JuggernautConfig*)data->config;
    if (!config) return;
    GunData *gun = &config->gun;

    // Optional: render different visual when enraged
    if (config->isEnraged) {
        // Visual indicator could be implemented here
    }

    Animation_Render(gun->resources.animation, 
        Camera_WorldVecToScreen(gun->state.position), 
        gun->animData.spriteSize,
        gun->state.angle,
        &gun->state.rotationCenter,
        gun->state.flip);
}

void Juggernaut_RenderParticles() {
    if (!JuggernautBulletEmitter) return;
    ParticleEmitter_Render(JuggernautBulletEmitter);
    ParticleEmitter_Render(JuggernautMuzzleFlashEmitter);
    ParticleEmitter_Render(JuggernautCasingEmitter);
    ParticleEmitter_Render(JuggernautBulletFragmentsEmitter);
}
