/**
 * @file vantage_render.c
 * @brief Renders Vantage enemy type
 * 
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_vantage.h>
#include <camera.h>
#include <app.h>
#include <circle.h>

void Vantage_Render(EnemyData* data) {
    VantageConfig *config = (VantageConfig*)data->config;
    if (!config) return;
    GunData *gun = &config->gun;

    Animation_Render(gun->resources.animation, 
        Camera_WorldVecToScreen(gun->state.position), 
        gun->animData.spriteSize,
        gun->state.angle,
        &gun->state.rotationCenter,
        gun->state.flip);
}

void Vantage_RenderParticles() {
    if (!VantageBulletEmitter) return;
    ParticleEmitter_Render(VantageBulletEmitter);
    ParticleEmitter_Render(VantageMuzzleFlashEmitter);
    ParticleEmitter_Render(VantageCasingEmitter);
    ParticleEmitter_Render(VantageBulletFragmentsEmitter);
}
