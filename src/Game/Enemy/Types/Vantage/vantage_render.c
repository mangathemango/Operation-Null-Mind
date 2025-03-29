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
    Animation_Render(
        gun->resources.animation, 
        Camera_WorldVecToScreen(gun->state.position), 
        gun->animData.spriteSize,
        gun->state.angle,
        &gun->state.rotationCenter,
        gun->state.flip
    );
    
    if (config->aiming || config->shooting) {
        Vantage_RenderLaser(data);
    }
}

void Vantage_RenderParticles() {
    if (!VantageBulletEmitter) return;
    ParticleEmitter_Render(VantageBulletEmitter);
    ParticleEmitter_Render(VantageMuzzleFlashEmitter);
    ParticleEmitter_Render(VantageCasingEmitter);
    ParticleEmitter_Render(VantageBulletFragmentsEmitter);
}

void Vantage_RenderLaser(EnemyData* data) {
    VantageConfig* config = (VantageConfig*)data->config;
    if (!config) return;
    GunData* gun = &config->gun;

    // Laser width configuration
    int lazerWidth = config->lazerWidth;
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
