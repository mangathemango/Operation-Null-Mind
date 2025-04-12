#include <enemy_libet.h>
#include <stdlib.h>

/**
 * @brief [OnDeath] Cleans up resources for the Libet boss enemy
 * 
 * Frees memory and destroys resources associated with the Libet boss enemy.
 * 
 * @param data Pointer to the enemy data structure
 */
void Libet_OnDeath(EnemyData* data) {
    LibetConfig* config = (LibetConfig*)data->config;
    if (!config) return;

    free(config);
    data->config = NULL;
}