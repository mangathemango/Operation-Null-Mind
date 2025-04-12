#include <enemy_sabot.h>
#include <animation.h>
#include <stdlib.h>

/**
 * @brief [OnDeath] Cleans up resources for Sabot enemy type
 *
 * Frees allocated memory and destroys resources associated with the Sabot enemy.
 *
 * @param data Pointer to the enemy data structure
 */
void Sabot_OnDeath(EnemyData* data) {
    SabotConfig* config = (SabotConfig*)data->config;
    if (!config) return;

    // Destroy animation resources
    Animation_Destroy(config->gun.resources.animation);

    // Free allocated memory for config
    free(config);
    data->config = NULL;
}