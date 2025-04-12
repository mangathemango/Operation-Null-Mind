#include <enemy_vantage.h>
#include <animation.h>
#include <stdlib.h>

void Vantage_OnDeath(EnemyData* data) {
    VantageConfig* config = (VantageConfig*)data->config;
    if (config) {
        GunData* gun = &config->gun;
        Animation_Destroy(gun->resources.animation);
        free(config);
        data->config = NULL;
    }
}