#include <enemy_kamikaze.h>
#include <stdlib.h>

/**
 * @brief [OnDeath] Cleans up resources for the Kamikaze enemy
 * 
 * Frees memory and destroys resources associated with the Kamikaze enemy.
 * 
 * @param data Pointer to the enemy data structure
 */
void Kamikaze_OnDeath(EnemyData* data) {
    KamikazeConfig* config = (KamikazeConfig*)data->config;
    if (!config) return;

    free(config);
    data->config = NULL;
}