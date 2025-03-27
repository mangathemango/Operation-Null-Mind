/**
 * @file vantage_start.c
 * @brief Initializes Vantage enemy instances
 *
 * Handles the creation and setup of Vantage enemies,
 * including their resources and initial state.
 * 
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_vantage.h>
#include <animation.h>
#include <circle.h>

/**
 * @brief [Start] Initializes a Vantage enemy instance
 * 
 * Sets up the Vantage enemy's resources including animations, 
 * particle effects, and timers.
 * 
 * @param data Pointer to the enemy data structure to initialize
 */
void Vantage_Start(EnemyData* data) {
    // Initialize animation resources
    data->resources.animation = Animation_Create(&data->animData);
    
    // Set up config pointer
    data->config = &VantageConfigData;
}
