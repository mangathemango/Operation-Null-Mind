/**
 * @file bullet_start.c
 * @brief Initializes the bullet system
 *
 * Sets up bullet resources, particle emitters, and initial
 * properties for the projectile system.
 *
 * @author Mango
 * @date 2025-03-05
 */

#include <bullet.h>
#include <particle_emitterpresets.h>
#include <gun.h>
#include <player.h>

/**
 * @brief [Start] Initializes the bullet system by creating particle emitters
 */
void Bullet_Start()
{
     //Set up bullet emitter presets
     ParticleEmitter* bulletEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_BulletDefault);
     ParticleEmitter* bulletFragmentEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_BulletFragments);
     for (int i = 0; i < GUN_COUNT; i++) {
          GunData *gun = GunList[i];
          gun->resources.bulletPreset = bulletEmitter;
          gun->resources.bulletFragmentEmitter = bulletFragmentEmitter;
     }  
}