/**
 * @file proxy_start.c
 * @brief Initializes Proxy enemy instances
 *
 * Handles the creation and setup of Proxy enemies,
 * including their resources and initial state.
 * 
 * @author Mango
 * @date 2025-03-20
 */

#include <enemy_proxy.h>
#include <animation.h>
#include <circle.h>
#include <particle_emitterpresets.h>

/**
 * @brief [Start] Initializes a Proxy enemy instance
 * 
 * Sets up the Proxy enemy's resources including animations, 
 * particle effects, and timers.
 * 
 * @param data Pointer to the enemy data structure to initialize
 */
void Proxy_Start(EnemyData* data) {
    // Set up config pointer
    data->config = malloc(sizeof(ProxyConfig));
    memcpy(data->config, &ProxyConfigData, sizeof(ProxyConfig));
    AnimationData animData = ((ProxyConfig*) data->config)->gun.animData;
    ((ProxyConfig*) data->config)->gun.resources.animation = Animation_Create(&animData);
    ((ProxyConfig*) data->config)->lastPosition = data->state.position;
    // Additional initialization will be implemented later
}
