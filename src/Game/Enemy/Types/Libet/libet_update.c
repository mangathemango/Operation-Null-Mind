#include <enemy_libet.h>
#include <time_system.h>

/**
 * @brief [Update] Updates the Libet boss enemy's state
 *
 * This function is called each frame to update the Libet boss enemy's behavior.
 *
 * @param data Pointer to the enemy data structure
 */
void Libet_Update(EnemyData* data) {
    LibetConfig* config = (LibetConfig*)data->config;
    config->timer += Time->deltaTimeSeconds;

    switch (config->state) {

    case LIBET_FLOATING:
        // Handle floating behavior
        if (config->timer >= config->floatTime) {
            config->state = LIBET_DIAGONAL_LAZER_CHARGING;
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if (x == 0 && y == 0) continue;
                    Vec2 direction = Vec2_Normalize((Vec2){x, y});
                    Lazer lazer = {
                        .active = true,
                        .startPosition = data->state.position,
                        .direction = direction,
                        .width = 5,
                        .damage = 0,
                        .lifeTime = 0.0f
                    };
                    Libet_AddLazer(lazer);
                }
            }
            config->timer = 0;
        }
        break;

    case LIBET_DIAGONAL_LAZER_CHARGING:
        for (int i = 0; i < 40; i++) {
            if (libetLazers[i].active) {
                libetLazers[i].startPosition = data->state.position;
                libetLazers[i].width = 0;
            }
        }
        // Handle diagonal lazer charging behavior
        if (config->timer >= config->lazerChargeTime) {
            config->state = LIBET_DIAGONAL_LAZER_FIRING;
            config->timer = 0;
        }
        break;
    
    case LIBET_DIAGONAL_LAZER_FIRING:
        // Handle diagonal lazer firing behavior
        for (int i = 0; i < 40; i++) {
            if (libetLazers[i].active) {
                libetLazers[i].startPosition = data->state.position;
                libetLazers[i].width = 5 - config->timer / config->lazerFireTime * 5;
                libetLazers[i].damage = 20;
            }
        }
        if (config->timer >= config->lazerFireTime) {
            for (int i = 0; i < 40; i++) {
                libetLazers[i].active = false;
            }
            config->state = LIBET_FLOATING;
            config->timer = 0;
        }
        break;

    default:
        config->state = LIBET_FLOATING;
        break;
    }
    for (int i = 0; i < 40; i++) {
        if (libetLazers[i].active) {
            Lazer_Update(&libetLazers[i]);
        }
    }
}

void Libet_AddLazer(Lazer lazer) {
    for (int i = 0; i < 40; i++) {
        if (!libetLazers[i].active) {
            libetLazers[i] = lazer;
            libetLazers[i].active = true;
            break;
        }
    }
}