/**
 * @file radius_start.c
 * @brief Initializes Radius enemy instances
 *
 * Handles the creation and setup of Radius enemies,
 * including their resources and initial state.
 * 
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_radius.h>
#include <animation.h>
#include <circle.h>

/**
 * @brief [Start] Initializes a Radius enemy instance
 * 
 * Sets up the Radius enemy's resources including animations, 
 * particle effects, and timers.
 * 
 * @param data Pointer to the enemy data structure to initialize
 */
void Radius_Start(EnemyData* data) {
    // Initialize animation resources
    data->resources.animation = Animation_Create(&data->animData);
    
    // Set up config pointer
    data->config = &RadiusConfigData;
}
