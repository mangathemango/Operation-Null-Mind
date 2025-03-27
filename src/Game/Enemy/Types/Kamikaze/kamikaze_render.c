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
 * This function handles the rendering of the Echo enemy type,
 * including its special visual effects like transparency and afterimages.
 * 
 * @param data Pointer to the enemy data structure
 */
void Kamikaze_Render(EnemyData* data) {
    KamikazeConfig *config = data->config;
    if (config->exploding) {
        float delay = 0.5f;
        if (config->explosionTimer < delay) return;
        int a = (50 * (config->explosionTimer - delay) / (1.5f - delay));



        DrawFilledCircle(
            Camera_WorldVecToScreen(data->state.position), 
            config->explosionRadius, 
            (SDL_Color){255, 0, 0, a}
        );
    }
}