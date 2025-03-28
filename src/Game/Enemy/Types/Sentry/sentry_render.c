/**
 * @file sentry_render.c
 * @brief Renders Sentry enemy type
 * 
 * Handles the visual presentation of Sentry enemies.
 * 
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_sentry.h>
#include <camera.h>
#include <app.h>
#include <circle.h>

/**
 * @brief [Render] Renders the Sentry enemy
 * 
 * This function handles the rendering of the Sentry enemy type.
 * 
 * @param data Pointer to the enemy data structure
 */
void Sentry_Render(EnemyData* data) {
    SentryConfig *config = (SentryConfig*)data->config;
    if (!config) return;
    GunData *gun = &config->gun;

    // Optionally render alert indicator when alerted
    if (config->isAlerted) {
        // Visual indicator for alerted state could be added here
    }

    Animation_Render(gun->resources.animation, 
        Camera_WorldVecToScreen(gun->state.position), 
        gun->animData.spriteSize,
        gun->state.angle,
        &gun->state.rotationCenter,
        gun->state.flip);
}

void Sentry_RenderParticles() {
    if (!SentryBulletEmitter) return;
    ParticleEmitter_Render(SentryBulletEmitter);
    ParticleEmitter_Render(SentryMuzzleFlashEmitter);
    ParticleEmitter_Render(SentryCasingEmitter);
    ParticleEmitter_Render(SentryBulletFragmentsEmitter);
}
