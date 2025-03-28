/**
 * @file proxy_render.c
 * @brief Renders Proxy enemy type
 *
 * Handles the visual presentation of Proxy enemies.
 * 
 * @author Mango
 * @date 2025-03-20
 */

#include <enemy_proxy.h>
#include <camera.h>
#include <app.h>
#include <circle.h>

/**
 * @brief [Render] Renders the Proxy enemy
 * 
 * This function handles the rendering of the Proxy enemy type.
 * When deployed, it also renders the proxy's influence radius.
 * 
 * @param data Pointer to the enemy data structure
 */
void Proxy_Render(EnemyData* data) {
    // Rendering will be implemented later
    ProxyConfig *config = (ProxyConfig*)data->config;

    Vec2 offset = Vec2_Add(config->gun.config.gripPosition, config->gunOffset);
    if (data->state.flip == SDL_FLIP_HORIZONTAL) offset.x = -offset.x;
    config->gun.state.rotationCenter = Vec2_ToPoint(
        config->gun.config.gripPosition
    );
    Vec2 renderPosition = Vec2_ToCenteredPosition(
        Camera_WorldVecToScreen(
            Vec2_Add(data->state.position, offset)
        ),
        config->gun.animData.frameSize
    );

    Animation_Render(
        config->gun.resources.animation,
        renderPosition,
        config->gun.animData.frameSize,
        config->gun.state.angle,
        &config->gun.state.rotationCenter,
        data->state.flip
    );
}
