/**
 * @file recharge_render.c
 * @brief Renders Recharge enemy type
 *
 * Handles the visual presentation of Recharge enemies.
 * 
 * @date 2025-03-05
 */

#include <enemy_recharge.h>
#include <camera.h>
#include <app.h>
#include <circle.h>
#include <math.h>

/**
 * @brief [Render] Renders the Recharge enemy
 * 
 * This function handles the rendering of the Recharge enemy type.
 * 
 * @param data Pointer to the enemy data structure
 */
void Recharge_Render(EnemyData* data) {
    RechargeConfig* config = (RechargeConfig*)data->config;


    if (config->isRecharging) {
        float timePassedRatio = config->timer / config->rechargeDuration;
        int alpha = 255 - 255 * timePassedRatio;
        SDL_SetTextureAlphaMod(config->rechargeTexture, alpha);
    
        float radius = config->rechargeRadius * sqrt(timePassedRatio);
        SDL_Rect dest = Vec2_ToCenteredSquareRect(
            Camera_WorldVecToScreen(config->rechargePosition),
            radius * 2
         );
        SDL_RenderCopy(app.resources.renderer, config->rechargeTexture, NULL, &dest);
    }
}