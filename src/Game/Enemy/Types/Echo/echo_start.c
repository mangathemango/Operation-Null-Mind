/**
 * @file echo_start.c
 * @brief Initializes Echo enemy instances
 *
 * Handles the creation and setup of Echo enemies,
 * including their resources and initial state.
 * 
 * @author Mango
 * @date 2025-03-22
 */

#include <enemy_echo.h>
#include <animation.h>
#include <circle.h>
#include <particle_emitterpresets.h>
#include <random.h>

ParticleEmitter* EchoBulletEmitter;
ParticleEmitter* EchoMuzzleFlashEmitter;
ParticleEmitter* EchoCasingEmitter;
ParticleEmitter* EchoBulletFragmentsEmitter;

/**
 * @brief [Start] Initializes an Echo enemy instance
 * 
 * Sets up the Echo enemy's resources including animations, 
 * particle effects, and timers.
 * 
 * @param data Pointer to the enemy data structure to initialize
 */
void Echo_Start(EnemyData* data) {
    data->config = malloc(sizeof(EchoConfig));
    memcpy(data->config, &EchoConfigData, sizeof(EchoConfig));
    AnimationData animData = ((EchoConfig*) data->config)->gun.animData;

    ((EchoConfig*) data->config)->lastPosition = data->state.position;
    ((EchoConfig*) data->config)->directionChangeTime = RandFloat(1.0f, 3.0f);
    ((EchoConfig*) data->config)->directionChangeTimer = 3.0f;
    ((EchoConfig*) data->config)->shootTime = RandFloat(
        data->stats.attackCooldown / 2, data->stats.attackCooldown * 3 / 2
    );
    
    GunData* gun = &((EchoConfig*) data->config)->gun;
    gun->resources.animation = Animation_Create(&animData);
    gun->resources.bulletPreset = EchoBulletEmitter;
    gun->resources.casingParticleEmitter = EchoCasingEmitter;
    gun->resources.muzzleFlashEmitter = EchoMuzzleFlashEmitter;
    gun->resources.bulletFragmentEmitter = EchoBulletFragmentsEmitter;
}