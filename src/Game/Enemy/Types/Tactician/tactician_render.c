/**
 * @file tactician_render.c
 * @brief Renders Tactician enemy type
 */

#include <enemy_tactician.h>
#include <camera.h>
#include <app.h>
#include <circle.h>

void Tactician_Render(EnemyData* data) {
    TacticianConfig *config = (TacticianConfig*)data->config;
    if (!config) return;
    GunData *gun = &config->gun;


    Animation_Render(gun->resources.animation, 
        Camera_WorldVecToScreen(gun->state.position), 
        gun->animData.spriteSize,
        gun->state.angle,
        &gun->state.rotationCenter,
        gun->state.flip);
}

void Tactician_RenderParticles() {
    if (!TacticianBulletEmitter) return;
    ParticleEmitter_Render(TacticianBulletEmitter);
    ParticleEmitter_Render(TacticianMuzzleFlashEmitter);
    ParticleEmitter_Render(TacticianCasingEmitter);
    ParticleEmitter_Render(TacticianBulletFragmentsEmitter);
}
