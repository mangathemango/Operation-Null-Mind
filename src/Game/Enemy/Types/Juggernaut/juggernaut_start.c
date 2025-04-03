/**
 * @file juggernaut_start.c
 * @brief Initializes Juggernaut enemy instances
 *
 * Handles the creation and setup of Juggernaut enemies,
 * including their resources and initial state.
 * 
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_juggernaut.h>
#include <animation.h>
#include <circle.h>
#include <particle_emitterpresets.h>
#include <random.h>

ParticleEmitter* JuggernautBulletEmitter;
ParticleEmitter* JuggernautMuzzleFlashEmitter;
ParticleEmitter* JuggernautCasingEmitter;
ParticleEmitter* JuggernautBulletFragmentsEmitter;

/**
 * @brief [Start] Initializes a Juggernaut enemy instance
 * 
 * Sets up the Juggernaut enemy's resources including animations, 
 * particle effects, and timers.
 * 
 * @param data Pointer to the enemy data structure to initialize
 */
void Juggernaut_Start(EnemyData* data) {
    data->config = malloc(sizeof(JuggernautConfig));
    memcpy(data->config, &JuggernautConfigData, sizeof(JuggernautConfig));
    AnimationData animData = ((JuggernautConfig*) data->config)->gun.animData;

    ((JuggernautConfig*) data->config)->lastPosition = data->state.position;
    ((JuggernautConfig*) data->config)->directionChangeTime = RandFloat(1.0f, 3.0f);
    ((JuggernautConfig*) data->config)->directionChangeTimer = 3.0f;
    ((JuggernautConfig*) data->config)->walkDuration = RandFloat(2.0f, 4.0f);
    ((JuggernautConfig*) data->config)->spinSpeedDegrees = RandFloat(360, 720);
    
    GunData* gun = &((JuggernautConfig*) data->config)->gun;
    gun->resources.animation = Animation_Create(&animData);
    gun->resources.bulletPreset = JuggernautBulletEmitter;
    gun->resources.casingParticleEmitter = JuggernautCasingEmitter;
    gun->resources.muzzleFlashEmitter = JuggernautMuzzleFlashEmitter;
    gun->resources.bulletFragmentEmitter = JuggernautBulletFragmentsEmitter;
}
