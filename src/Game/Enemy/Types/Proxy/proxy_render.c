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
    if (!config) return;
    GunData *gun = config->gun;

    Animation_Render(gun->resources.animation, 
        Camera_WorldVecToScreen(gun->state.position), 
        gun->animData.spriteSize,
        gun->state.angle,
        &gun->state.rotationCenter,
        gun->state.flip);

}
