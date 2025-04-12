#include <enemy_tactician.h>
#include <animation.h>
#include <stdlib.h>

/**
 * @brief [OnDeath] Cleans up resources for the Tactician enemy
 * 
 * Frees memory and destroys resources associated with the Tactician enemy.
 * 
 * @param data Pointer to the enemy data structure
 */
void Tactician_OnDeath(EnemyData* data) {
    TacticianConfig* config = (TacticianConfig*)data->config;
    if (!config) return;

    GunData* gun = &config->gun;
    Animation_Destroy(gun->resources.animation);

    free(config);
    data->config = NULL;
}