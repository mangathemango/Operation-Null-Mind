/**
 * @file bullet_render.c
 * @brief Handles rendering of bullets and impact effects
 *
 * Manages the visual representation of bullets, tracer effects,
 * and bullet impact particles.
 *
 * @author Mango
 * @date 2025-03-05
 */

#include <bullet.h>
#include <particle_emitterpresets.h>
#include <player.h>

/**
 * @brief [Render] Renders all active bullets and bullet fragments
 * 
 * Draws all active bullet particles and their impact fragments
 * from the current weapon's emitters.
 */
void Bullet_Render()
{
    GunData* gun = player.state.currentGun;

    ParticleEmitter_Render(gun->resources.bulletPreset);

    ParticleEmitter_Render(gun->resources.bulletFragmentEmitter);
}