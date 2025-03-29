/**
 * @file radius_start.c
 * @brief Initializes Radius enemy instances
 *
 * Handles the creation and setup of Radius enemies,
 * including their resources and initial state.
 * 
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_radius.h>
#include <animation.h>
#include <circle.h>
#include <particle_emitterpresets.h>
#include <random.h>

ParticleEmitter* RadiusBulletEmitter;
ParticleEmitter* RadiusMuzzleFlashEmitter;
ParticleEmitter* RadiusCasingEmitter;
ParticleEmitter* RadiusBulletFragmentsEmitter;
ParticleEmitter* RadiusExplosionEmitter;
SDL_Texture* RadiusExplosionIndicator;

/**
 * @brief [Start] Initializes a Radius enemy instance
 * 
 * Sets up the Radius enemy's resources including animations, 
 * particle effects, and timers.
 * 
 * @param data Pointer to the enemy data structure to initialize
 */
void Radius_Start(EnemyData* data) {
    data->config = malloc(sizeof(RadiusConfig));
    memcpy(data->config, &RadiusConfigData, sizeof(RadiusConfig));
    AnimationData animData = ((RadiusConfig*) data->config)->gun.animData;

    ((RadiusConfig*) data->config)->lastPosition = data->state.position;
    ((RadiusConfig*) data->config)->directionChangeTime = RandFloat(1.0f, 3.0f);
    ((RadiusConfig*) data->config)->directionChangeTimer = 3.0f;
    ((RadiusConfig*) data->config)->shootTime = RandFloat(
        data->stats.attackCooldown / 2, data->stats.attackCooldown * 3 / 2
    );

    
    GunData* gun = &((RadiusConfig*) data->config)->gun;
    gun->resources.animation = Animation_Create(&animData);
    gun->resources.bulletPreset = RadiusBulletEmitter;
    gun->resources.casingParticleEmitter = RadiusCasingEmitter;
    gun->resources.muzzleFlashEmitter = RadiusMuzzleFlashEmitter;
    gun->resources.bulletFragmentEmitter = RadiusBulletFragmentsEmitter;
}
