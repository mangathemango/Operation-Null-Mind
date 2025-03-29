/**
 * @file echo_render.c
 * @brief Renders Echo enemy type
 * 
 * Handles the visual presentation of Echo enemies.
 * 
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_echo.h>
#include <camera.h>
#include <app.h>
#include <circle.h>

/**
 * @brief [Render] Renders the Echo enemy
 * 
 * This function handles the rendering of the Echo enemy type.
 * 
 * @param data Pointer to the enemy data structure
 */
void Echo_Render(EnemyData* data) {
    EchoConfig *config = (EchoConfig*)data->config;
    if (!config) return;
    GunData *gun = &config->gun;

    Animation_Render(gun->resources.animation, 
        Camera_WorldVecToScreen(gun->state.position), 
        gun->animData.spriteSize,
        gun->state.angle,
        &gun->state.rotationCenter,
        gun->state.flip);
}

void Echo_RenderParticles() {
    if (!EchoBulletEmitter) return;
    ParticleEmitter_Render(EchoBulletEmitter);
    ParticleEmitter_Render(EchoMuzzleFlashEmitter);
    ParticleEmitter_Render(EchoCasingEmitter);
    ParticleEmitter_Render(EchoBulletFragmentsEmitter);
}