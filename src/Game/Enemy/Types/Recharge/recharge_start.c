/**
 * @file recharge_start.c
 * @brief Initializes Recharge enemy instances
 *
 * Handles the creation and setup of Recharge enemies,
 * including their resources and initial state.
 * 
 * @author Mango
 * @date 2025-03-05
 */

#include <enemy_recharge.h>
#include <animation.h>
#include <circle.h>
#include <particle_emitterpresets.h>
#include <random.h>


/**
 * @brief [Start] Initializes a Recharge enemy instance
 * 
 * Sets up the Recharge enemy's resources including animations, 
 * particle effects, and timers.
 * 
 * @param data Pointer to the enemy data structure to initialize
 */
void Recharge_Start(EnemyData* data) {
    if (RechargeConfigData.rechargeTexture == NULL) {
        RechargeConfigData.rechargeTexture = CreateCircleOutlineTexture(
            RechargeConfigData.rechargeRadius, 
            (SDL_Color) {255, 255, 0, 255},
            2
        );
    }

    // Set up config pointer
    data->config = malloc(sizeof(RechargeConfig));
    memcpy(data->config, &RechargeConfigData, sizeof(RechargeConfig));
    ((RechargeConfig*) data->config)->rechargeCooldown = RandFloat(1.0f,3.0f);
}