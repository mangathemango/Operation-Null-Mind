#include <enemy_juggernaut.h>
#include <animation.h>
#include <stdlib.h>

/**
 * @brief [OnDeath] Cleans up resources for the Juggernaut enemy
 * 
 * Frees memory and destroys resources associated with the Juggernaut enemy.
 * 
 * @param data Pointer to the enemy data structure
 */
void Juggernaut_OnDeath(EnemyData* data) {
    JuggernautConfig* config = (JuggernautConfig*)data->config;
    if (!config) return;

    GunData* gun = &config->gun;
    Animation_Destroy(gun->resources.animation);

    free(config);
    data->config = NULL;
}