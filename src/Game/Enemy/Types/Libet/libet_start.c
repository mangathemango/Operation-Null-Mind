#include <enemy_libet.h>
#include <animation.h>
#include <random.h>
#include <particle_emitterpresets.h>

Lazer libetLazers[40] = {
    {
        .active = false,
        .startPosition = {0, 0},
        .direction = {0, 0},
        .endPosition = {0, 0},
        .width = 5,
        .damage = 0,
        .lifeTime = 0.0f
    }
};

ParticleEmitter* LibetBulletEmitter;

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
    memcpy(config, &LibetConfigData, sizeof(LibetConfig));

    // Initialize bullet emitter
    LibetBulletEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_BulletEnemy);
    ParticleEmitter_SetMaxParticles(LibetBulletEmitter, 1000);
}