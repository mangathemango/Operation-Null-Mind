/**
 * @file echo_start.c
 * @brief Initializes Echo enemy instances
 *
 * Handles the creation and setup of Echo enemies,
 * including their resources and initial state.
 * 
 * @author Mango
 * @date 2025-03-05
 */

#include <enemy_kamikaze.h>
#include <animation.h>
#include <circle.h>
#include <particle_emitterpresets.h>

ParticleEmitter* KamikazeExplosionEmitter = NULL;

/**
 * @brief [Start] Initializes an Echo enemy instance
 * 
 * Sets up the Echo enemy's resources including animations, 
 * particle effects, and timers.
 * 
 * @param data Pointer to the enemy data structure to initialize
 */
void Kamikaze_Start(EnemyData* data) {
    KamikazeConfigData.explosionIndicator = CreateCircleTexture(
        KamikazeConfigData.explosionRadius,
        (SDL_Color){255, 0, 0, 255}
    );
    if (!KamikazeExplosionEmitter) 
        KamikazeExplosionEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_Explosion);
    data->config = malloc(sizeof(KamikazeConfig));
    *(KamikazeConfig*)data->config = KamikazeConfigData;
}