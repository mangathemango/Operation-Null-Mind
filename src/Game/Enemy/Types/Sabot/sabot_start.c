/**
 * @file sabot_start.c
 * @brief Initializes Sabot enemy instances
 *
 * Handles the creation and setup of Sabot enemies,
 * including their resources and initial state.
 * 
 * @author Mango
 * @date 2025-03-21
 */

#include <enemy_sabot.h>
#include <animation.h>
#include <circle.h>
#include <particle_emitterpresets.h>
#include <random.h>

ParticleEmitter* SabotBulletEmitter;
ParticleEmitter* SabotMuzzleFlashEmitter;
ParticleEmitter* SabotCasingEmitter;
ParticleEmitter* SabotBulletFragmentsEmitter;

/**
 * @brief [Start] Initializes a Sabot enemy instance
 * 
 * Sets up the Sabot enemy's resources including animations, 
 * particle effects, and timers.
 * 
 * @param data Pointer to the enemy data structure to initialize
 */
void Sabot_Start(EnemyData* data) {
    // Initialize animation resources
    data->resources.animation = Animation_Create(&data->animData);
    
    // Set up config pointer
    data->config = malloc(sizeof(SabotConfig));
    memcpy(data->config, &SabotConfigData, sizeof(SabotConfig));
    AnimationData animData = ((SabotConfig*) data->config)->gun.animData;

    ((SabotConfig*) data->config)->lastPosition = data->state.position;
    ((SabotConfig*) data->config)->directionChangeTime = RandFloat(1.0f, 3.0f);
    ((SabotConfig*) data->config)->directionChangeTimer = 3.0f;
    ((SabotConfig*) data->config)->shootTime = RandFloat(
        data->stats.attackCooldown / 2, data->stats.attackCooldown * 3 / 2
    );
    GunData* gun = &((SabotConfig*) data->config)->gun;
    gun->resources.animation = Animation_Create(&animData);

    // Explicitly assign each resource - make sure the assignments take effect
    gun->resources.bulletPreset = SabotBulletEmitter;
    gun->resources.muzzleFlashEmitter = SabotMuzzleFlashEmitter;
    gun->resources.casingParticleEmitter = SabotCasingEmitter;
    gun->resources.bulletFragmentEmitter = SabotBulletFragmentsEmitter;
}
