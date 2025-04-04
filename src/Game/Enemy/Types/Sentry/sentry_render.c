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
#include <math.h>

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

    Animation_Render(
        gun->resources.animation, 
        Camera_WorldVecToScreen(gun->state.position), 
        gun->animData.spriteSize,
        gun->state.angle,
        &gun->state.rotationCenter,
        gun->state.flip
    );
    
    if (config->state == SENTRY_STATE_IDLE) {
        config->lazerWidth -= 10 * Time->deltaTimeSeconds; // Decrease laser width over time
        if (config->lazerWidth < 0) {
            config->lazerWidth = -1;
        }
        Sentry_RenderLaser(data);
    }

    if (config->state == SENTRY_STATE_AIMING) {
        config->lazerWidth = 0;
        Sentry_RenderLaser(data);
    }
    if (config->state == SENTRY_STATE_SHOOTING) {
        config->lazerWidth = 4 +  sinf(config->timer * 50); // Set laser width to 5 when shooting
        Sentry_RenderLaser(data);
    }
}

void Sentry_RenderLaser(EnemyData* data) {
    SentryConfig* config = (SentryConfig*)data->config;
    if (!config) return;
    GunData* gun = &config->gun;

    // Laser width configuration
    int lazerWidth = config->lazerWidth;
    if (lazerWidth < 0) return; // Don't draw if laser width is negative
    // Draw the red outer glow
    SDL_SetRenderDrawColor(app.resources.renderer, 255, 0, 0, 255);
    Vec2 lazerStart = Camera_WorldVecToScreen(config->lazerStart);
    Vec2 lazerEnd = Camera_WorldVecToScreen(config->lazerEnd);
    // Draw multiple red lines based on lazerWidth
    for (int dx = -lazerWidth; dx <= lazerWidth; dx++) {
        for (int dy = -lazerWidth; dy <= lazerWidth; dy++) {
            // Skip the center point and points too far from center (for a circular appearance)
            if ((dx == 0 && dy == 0) || (dx*dx + dy*dy > lazerWidth*lazerWidth)) {
                continue;
            }

            SDL_RenderDrawLine(
                app.resources.renderer, 
                lazerStart.x + dx, 
                lazerStart.y + dy, 
                lazerEnd.x + dx, 
                lazerEnd.y + dy
            );
        }
    }

    // Draw the white center line
    if (lazerWidth > 0) {
        SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
    }
    SDL_RenderDrawLine(
        app.resources.renderer, 
        lazerStart.x, 
        lazerStart.y, 
        lazerEnd.x, 
        lazerEnd.y
    );
}

void Sentry_RenderParticles() {
    if (!SentryBulletEmitter) return;
    ParticleEmitter_Render(SentryBulletEmitter);
    ParticleEmitter_Render(SentryMuzzleFlashEmitter);
    ParticleEmitter_Render(SentryCasingEmitter);
    ParticleEmitter_Render(SentryBulletFragmentsEmitter);
}
