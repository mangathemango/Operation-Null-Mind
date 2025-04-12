#include <enemy_recharge.h>
#include <stdlib.h>

/**
 * @brief [OnDeath] Cleans up resources for the Recharge enemy
 * 
 * Frees memory and destroys resources associated with the Recharge enemy.
 * 
 * @param data Pointer to the enemy data structure
 */
void Recharge_OnDeath(EnemyData* data) {
    RechargeConfig* config = (RechargeConfig*)data->config;
    if (!config) return;

    free(config);
    data->config = NULL;
}