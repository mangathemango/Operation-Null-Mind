/**
 * @file sentry_start.c
 * @brief Initializes Sentry enemy instances
 *
 * Handles the creation and setup of Sentry enemies,
 * including their resources and initial state.
 * 
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_sentry.h>
#include <animation.h>
#include <circle.h>
#include <particle_emitterpresets.h>
#include <random.h>

ParticleEmitter* SentryBulletEmitter;
ParticleEmitter* SentryMuzzleFlashEmitter;
ParticleEmitter* SentryCasingEmitter;
ParticleEmitter* SentryBulletFragmentsEmitter;

/**
 * @brief [Start] Initializes a Sentry enemy instance
 * 
 * Sets up the Sentry enemy's resources including animations, 
 * particle effects, and timers.
 * 
 * @param data Pointer to the enemy data structure to initialize
 */
void Sentry_Start(EnemyData* data) {
    data->config = malloc(sizeof(SentryConfig));
    memcpy(data->config, &SentryConfigData, sizeof(SentryConfig));
    AnimationData animData = ((SentryConfig*) data->config)->gun.animData;

    ((SentryConfig*) data->config)->lastPosition = data->state.position;
    ((SentryConfig*) data->config)->idleTime = RandFloat(
        data->stats.attackCooldown / 2, data->stats.attackCooldown * 3 / 2
    );


    GunData* gun = &((SentryConfig*) data->config)->gun;
    gun->resources.animation = Animation_Create(&animData);
    gun->resources.bulletPreset = SentryBulletEmitter;
    gun->resources.casingParticleEmitter = SentryCasingEmitter;
    gun->resources.muzzleFlashEmitter = SentryMuzzleFlashEmitter;
    gun->resources.bulletFragmentEmitter = SentryBulletFragmentsEmitter;
}
