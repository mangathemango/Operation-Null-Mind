/**
 * @file proxy_start.c
 * @brief Initializes Proxy enemy instances
 *
 * Handles the creation and setup of Proxy enemies,
 * including their resources and initial state.
 * 
 * @author Mango
 * @date 2025-03-20
 */

#include <enemy_proxy.h>
#include <animation.h>
#include <circle.h>
#include <particle_emitterpresets.h>
#include <random.h>

ParticleEmitter* ProxyBulletEmitter;
ParticleEmitter* ProxyMuzzleFlashEmitter;
ParticleEmitter* ProxyCasingEmitter;
ParticleEmitter* ProxyBulletFragmentsEmitter;

/**
 * @brief [Start] Initializes a Proxy enemy instance
 * 
 * Sets up the Proxy enemy's resources including animations, 
 * particle effects, and timers.
 * 
 * @param data Pointer to the enemy data structure to initialize
 */
void Proxy_Start(EnemyData* data) {
    if (!ProxyBulletEmitter) {
        ProxyGunData.resources.bulletPreset = ParticleEmitter_CreateFromPreset(ParticleEmitter_BulletEnemy);
        ProxyGunData.resources.muzzleFlashEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_MuzzleFlash);
        ProxyGunData.resources.casingParticleEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_PistolSMGCasing);
        ProxyGunData.resources.bulletFragmentEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_BulletFragments);
        ProxyGunData.resources.animation = Animation_Create(&ProxyGunData.animData);
    }
    // Set up config pointer
    data->config = malloc(sizeof(ProxyConfig));
    memcpy(data->config, &ProxyConfigData, sizeof(ProxyConfig));

    ((ProxyConfig*) data->config)->lastPosition = data->state.position;
    ((ProxyConfig*) data->config)->directionChangeTime = RandFloat(1.0f, 3.0f);
    ((ProxyConfig*) data->config)->directionChangeTimer = 3.0f;
    ((ProxyConfig*) data->config)->shootTimer = 0;
    ((ProxyConfig*) data->config)->shootTime = RandFloat(
        data->stats.attackCooldown / 2, data->stats.attackCooldown * 3 / 2
    );
    // Additional initialization will be implemented later
}
