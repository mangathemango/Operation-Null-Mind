#include <enemy_proxy.h>
#include <animation.h>
#include <stdlib.h>

/**
 * @brief [OnDeath] Cleans up resources for Proxy enemy type
 *
 * Frees allocated memory and destroys resources associated with the Proxy enemy.
 *
 * @param data Pointer to the enemy data structure
 */
void Proxy_OnDeath(EnemyData* data) {
    ProxyConfig* config = (ProxyConfig*)data->config;
    if (!config) return;

    // Destroy animation resources
    Animation_Destroy(config->gun.resources.animation);

    // Free allocated memory for config
    free(config);
    data->config = NULL;
}