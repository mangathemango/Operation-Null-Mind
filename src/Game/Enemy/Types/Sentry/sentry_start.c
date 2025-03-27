/**
 * @file sentry_start.c
 * @brief Initializes Sentry enemy instances
 *
 * Handles the creation and setup of Sentry enemies,
 * including their resources and initial state.
 * 
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_sentry.h>
#include <animation.h>
#include <circle.h>

/**
 * @brief [Start] Initializes a Sentry enemy instance
 * 
 * Sets up the Sentry enemy's resources including animations, 
 * particle effects, and timers.
 * 
 * @param data Pointer to the enemy data structure to initialize
 */
void Sentry_Start(EnemyData* data) {
    // Initialize animation resources
    data->resources.animation = Animation_Create(&data->animData);
    
    // Set up config pointer
    data->config = &SentryConfigData;
    
    // Save initial position as guard position
    SentryConfig* config = (SentryConfig*)data->config;
    config->guardPosition = data->state.position;
}
