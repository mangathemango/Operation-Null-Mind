/**
 * @file tactician_start.c
 * @brief Initializes Tactician enemy instances
 *
 * Handles the creation and setup of Tactician enemies,
 * including their resources and initial state.
 * 
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_tactician.h>
#include <animation.h>
#include <circle.h>
#include <particle_emitterpresets.h>
#include <random.h>

ParticleEmitter* TacticianBulletEmitter;
ParticleEmitter* TacticianMuzzleFlashEmitter;
ParticleEmitter* TacticianCasingEmitter;
ParticleEmitter* TacticianBulletFragmentsEmitter;
ParticleEmitter* TacticianBuffEffectEmitter;

/**
 * @brief [Start] Initializes a Tactician enemy instance
 * 
 * Sets up the Tactician enemy's resources including animations, 
 * particle effects, and timers.
 * 
 * @param data Pointer to the enemy data structure to initialize
 */
void Tactician_Start(EnemyData* data) {
    data->config = malloc(sizeof(TacticianConfig));
    memcpy(data->config, &TacticianConfigData, sizeof(TacticianConfig));
    AnimationData animData = ((TacticianConfig*) data->config)->gun.animData;

    ((TacticianConfig*) data->config)->lastPosition = data->state.position;
    ((TacticianConfig*) data->config)->directionChangeTime = RandFloat(1.0f, 3.0f);
    ((TacticianConfig*) data->config)->directionChangeTimer = 3.0f;
    ((TacticianConfig*) data->config)->shootTime = RandFloat(
        data->stats.attackCooldown / 2, data->stats.attackCooldown * 3 / 2
    );
    GunData* gun = &((TacticianConfig*) data->config)->gun;
    gun->resources.animation = Animation_Create(&animData);
    gun->resources.bulletPreset = TacticianBulletEmitter;
    gun->resources.casingParticleEmitter = TacticianCasingEmitter;
    gun->resources.muzzleFlashEmitter = TacticianMuzzleFlashEmitter;
    gun->resources.bulletFragmentEmitter = TacticianBulletFragmentsEmitter;
}
