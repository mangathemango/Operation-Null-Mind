/**
 * @file tactician_render.c
 * @brief Renders Tactician enemy type
 */

#include <enemy_tactician.h>
#include <camera.h>
#include <app.h>
#include <circle.h>
#include <math.h>

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

    if (config->state & TACTICIAN_STATE_COMMANDING) {
        float timePassedRatio = config->commandTimer / config->commandTime;
        int alpha = 255 - 255 * timePassedRatio;
        SDL_SetTextureAlphaMod(TacticianBuffCircleTexture, alpha);
    
        float radius = config->commandRadius * sqrt(timePassedRatio);
        SDL_Rect dest = Vec2_ToCenteredSquareRect(
            Camera_WorldVecToScreen(data->state.position),
            radius * 2
         );
        SDL_RenderCopy(app.resources.renderer, TacticianBuffCircleTexture, NULL, &dest);
    }
}

void Tactician_RenderParticles() {
    if (!TacticianBulletEmitter) return;
    ParticleEmitter_Render(TacticianBulletEmitter);
    ParticleEmitter_Render(TacticianMuzzleFlashEmitter);
    ParticleEmitter_Render(TacticianCasingEmitter);
    ParticleEmitter_Render(TacticianBulletFragmentsEmitter);
}
