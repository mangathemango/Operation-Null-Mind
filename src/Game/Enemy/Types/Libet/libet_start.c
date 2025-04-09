#include <enemy_libet.h>
#include <animation.h>
#include <random.h>

/**
 * @brief [Start] Initializes the Libet boss enemy instance
 *
 * Sets up the Libet boss enemy's resources and initial state.
 *
 * @param data Pointer to the enemy data structure to initialize
 */
void Libet_Start(EnemyData* data) {
    data->config = malloc(sizeof(LibetConfig));
    LibetConfig* config = (LibetConfig*)data->config;
}