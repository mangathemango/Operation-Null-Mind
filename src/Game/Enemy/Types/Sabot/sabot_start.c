/**
 * @file sabot_start.c
 * @brief Initializes Sabot enemy instances
 *
 * Handles the creation and setup of Sabot enemies,
 * including their resources and initial state.
 * 
 * @author Mango
 * @date 2025-03-21
 */

#include <enemy_sabot.h>
#include <animation.h>
#include <circle.h>
#include <particle_emitterpresets.h>

/**
 * @brief [Start] Initializes a Sabot enemy instance
 * 
 * Sets up the Sabot enemy's resources including animations, 
 * particle effects, and timers.
 * 
 * @param data Pointer to the enemy data structure to initialize
 */
void Sabot_Start(EnemyData* data) {
    // Initialize animation resources
    data->resources.animation = Animation_Create(&data->animData);
    
    // Set up config pointer
    data->config = &SabotConfigData;
    
    // Additional initialization will be implemented later
}
