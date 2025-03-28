/**
 * @file vantage_start.c
 * @brief Initializes Vantage enemy instances
 *
 * Handles the creation and setup of Vantage enemies,
 * including their resources and initial state.
 * 
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_vantage.h>
#include <animation.h>
#include <circle.h>
#include <particle_emitterpresets.h>
#include <random.h>

ParticleEmitter* VantageBulletEmitter;
ParticleEmitter* VantageMuzzleFlashEmitter;
ParticleEmitter* VantageCasingEmitter;
ParticleEmitter* VantageBulletFragmentsEmitter;

/**
 * @brief [Start] Initializes a Vantage enemy instance
 * 
 * Sets up the Vantage enemy's resources including animations, 
 * particle effects, and timers.
 * 
 * @param data Pointer to the enemy data structure to initialize
 */
void Vantage_Start(EnemyData* data) {
    data->config = malloc(sizeof(VantageConfig));
    memcpy(data->config, &VantageConfigData, sizeof(VantageConfig));
    AnimationData animData = ((VantageConfig*) data->config)->gun.animData;

    ((VantageConfig*) data->config)->lastPosition = data->state.position;
    ((VantageConfig*) data->config)->directionChangeTime = RandFloat(1.0f, 3.0f);
    ((VantageConfig*) data->config)->directionChangeTimer = 3.0f;
    ((VantageConfig*) data->config)->shootTime = RandFloat(
        data->stats.attackCooldown / 2, data->stats.attackCooldown * 3 / 2
    );
    GunData* gun = &((VantageConfig*) data->config)->gun;
    gun->resources.animation = Animation_Create(&animData);
    gun->resources.bulletPreset = VantageBulletEmitter;
    gun->resources.casingParticleEmitter = VantageCasingEmitter;
    gun->resources.muzzleFlashEmitter = VantageMuzzleFlashEmitter;
    gun->resources.bulletFragmentEmitter = VantageBulletFragmentsEmitter;
}
