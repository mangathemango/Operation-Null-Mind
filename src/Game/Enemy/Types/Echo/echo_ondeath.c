#include <enemy_echo.h>
#include <animation.h>
#include <stdlib.h>

/**
 * @brief [OnDeath] Cleans up resources for Echo enemy type
 *
 * Frees allocated memory and destroys resources associated with the Echo enemy.
 *
 * @param data Pointer to the enemy data structure
 */
void Echo_OnDeath(EnemyData* data) {
    EchoConfig* config = (EchoConfig*)data->config;
    if (!config) return;

    // Destroy animation resources
    Animation_Destroy(config->gun.resources.animation);

    // Free allocated memory for config
    free(config);
    data->config = NULL;
}