/**
 * @file juggernaut_start.c
 * @brief Initializes Juggernaut enemy instances
 *
 * Handles the creation and setup of Juggernaut enemies,
 * including their resources and initial state.
 * 
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_juggernaut.h>
#include <animation.h>
#include <circle.h>

/**
 * @brief [Start] Initializes a Juggernaut enemy instance
 * 
 * Sets up the Juggernaut enemy's resources including animations, 
 * particle effects, and timers.
 * 
 * @param data Pointer to the enemy data structure to initialize
 */
void Juggernaut_Start(EnemyData* data) {
    // Initialize animation resources
    data->resources.animation = Animation_Create(&data->animData);
    
    // Set up config pointer
    data->config = &JuggernautConfigData;
}
