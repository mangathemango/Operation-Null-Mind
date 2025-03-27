/**
 * @file tactician_start.c
 * @brief Initializes Tactician enemy instances
 *
 * Handles the creation and setup of Tactician enemies,
 * including their resources and initial state.
 * 
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_tactician.h>
#include <animation.h>
#include <circle.h>

/**
 * @brief [Start] Initializes a Tactician enemy instance
 * 
 * Sets up the Tactician enemy's resources including animations, 
 * particle effects, and timers.
 * 
 * @param data Pointer to the enemy data structure to initialize
 */
void Tactician_Start(EnemyData* data) {
    // Initialize animation resources
    data->resources.animation = Animation_Create(&data->animData);
    
    // Set up config pointer
    data->config = &TacticianConfigData;
}
