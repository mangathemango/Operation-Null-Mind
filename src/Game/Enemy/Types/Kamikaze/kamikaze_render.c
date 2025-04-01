/**
 * @file echo_render.c
 * @brief Renders Echo enemy type
 *
 * Handles the visual presentation of Echo enemies,
 * including special effects like transparency and afterimages.
 * 
 * @date 2025-03-05
 */

#include <enemy_kamikaze.h>
#include <camera.h>
#include <app.h>
#include <circle.h>

/**
 * @brief [Render] Renders the Echo enemy
 * 
 * Renders the kamikaze explosion indicator
 * 
 * @param data Pointer to the enemy data structure
 */
void Kamikaze_Render(EnemyData* data) {
    KamikazeConfig *config = data->config;
    if (config->state == KAMIKAZE_STATE_EXPLODING) {
        float delay = config->indicatorDelay;
        if (config->explosionTimer < delay) return;
        int a = (50 * (config->explosionTimer - delay) / (config->explosionTime - delay));
        SDL_Rect dest = Vec2_ToCenteredSquareRect(
            Camera_WorldVecToScreen(data->state.position), 
            config->explosionRadius * 2
        );

        SDL_SetTextureAlphaMod(config->explosionIndicator, a);
        if (!config->explosionIndicator) {
            config->explosionIndicator = CreateCircleTexture(
                KamikazeConfigData.explosionRadius,
                (SDL_Color){255, 0, 0, 255}
            );
        }
        SDL_RenderCopy(app.resources.renderer, config->explosionIndicator, NULL, &dest);
    }
}