/**
 * @file sabot_render.c
 * @brief Renders Sabot enemy type
 *
 * Handles the visual presentation of Sabot enemies.
 * 
 * @author Mango
 * @date 2025-03-21
 */

#include <enemy_sabot.h>
#include <camera.h>
#include <app.h>
#include <circle.h>

/**
 * @brief [Render] Renders the Sabot enemy
 * 
 * This function handles the rendering of the Sabot enemy type.
 * 
 * @param data Pointer to the enemy data structure
 */
void Sabot_Render(EnemyData* data) {
    SabotConfig *config = (SabotConfig*)data->config;
    if (!config) return;
    GunData *gun = &config->gun;

    Animation_Render(gun->resources.animation, 
        Camera_WorldVecToScreen(gun->state.position), 
        gun->animData.spriteSize,
        gun->state.angle,
        &gun->state.rotationCenter,
        gun->state.flip);
}

void Sabot_RenderParticles() {
    if (!SabotBulletEmitter) return;
    ParticleEmitter_Render(SabotBulletEmitter);
    ParticleEmitter_Render(SabotMuzzleFlashEmitter);
    ParticleEmitter_Render(SabotCasingEmitter);
    ParticleEmitter_Render(SabotBulletFragmentsEmitter);
    ParticleEmitter_Render(SabotExplosionEmitter);

    for (int i = 0; i < SabotBulletEmitter->maxParticles; i++) {
        Particle* bullet = &SabotBulletEmitter->particles[i];
        if (!bullet->alive) continue;
        float lifetimeRatio = bullet->timeAlive / bullet->maxLifeTime;
        int alpha = (lifetimeRatio) * 150;
        SDL_Rect dest = Vec2_ToCenteredSquareRect(
            Vec2_Add(
                Camera_WorldVecToScreen(bullet->position),
                Vec2_Divide(
                    bullet->size, 
                    2
                )
            ), 
            SabotConfigData.explosionRadius * 2
        );
        SDL_SetTextureAlphaMod(SabotExplosionIndicator, alpha);
        SDL_RenderCopy(
            app.resources.renderer, 
            SabotExplosionIndicator, 
            NULL, 
            &dest
        );
    }
}
