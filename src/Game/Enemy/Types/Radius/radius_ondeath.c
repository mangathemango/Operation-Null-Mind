#include <enemy_radius.h>
#include <stdlib.h>

/**
 * @brief [OnDeath] Cleans up resources for the Radius enemy
 * 
 * Frees memory and destroys resources associated with the Radius enemy.
 * 
 * @param data Pointer to the enemy data structure
 */
void Radius_OnDeath(EnemyData* data) {
    RadiusConfig* config = (RadiusConfig*)data->config;
    if (!config) return;

    free(config);
    data->config = NULL;
}