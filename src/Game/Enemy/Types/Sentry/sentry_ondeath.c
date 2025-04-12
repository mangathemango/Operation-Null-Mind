#include <enemy_sentry.h>
#include <animation.h>
#include <stdlib.h>

/**
 * @brief [OnDeath] Cleans up resources for the Sentry enemy
 * 
 * Frees memory and destroys resources associated with the Sentry enemy.
 * 
 * @param data Pointer to the enemy data structure
 */
void Sentry_OnDeath(EnemyData* data) {
    SentryConfig* config = (SentryConfig*)data->config;
    if (!config) return;

    GunData* gun = &config->gun;
    Animation_Destroy(gun->resources.animation);

    free(config);
    data->config = NULL;
}