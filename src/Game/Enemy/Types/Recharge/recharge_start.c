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

ParticleEmitter* RechargeEffectEmitter = NULL;

/**
 * @brief [Start] Initializes a Recharge enemy instance
 * 
 * Sets up the Recharge enemy's resources including animations, 
 * particle effects, and timers.
 * 
 * @param data Pointer to the enemy data structure to initialize
 */
void Recharge_Start(EnemyData* data) {
    // Initialize animation resources
    data->resources.animation = Animation_Create(&data->animData);
    
    // Set up config pointer
    data->config = &RechargeConfigData;
    
    // Initialize any other resources needed for Recharge enemy
    if (RechargeEffectEmitter == NULL) {
        // Initialize particle emitter for recharge effect if needed
    }
}