/**
 * @file gun_start.c
 * @brief Initializes the weapon system
 *
 * Sets up gun resources, animations, and particle effects for
 * all weapon types in the game.
 *
 * @author Mango
 * @date 2025-03-07
 */

//? Written by Mango on 07/03/2025

#include <gun.h>
#include <bullet.h>

/**
 * @brief [Start] Initializes all guns and their particle emitters
 * 
 * Populates the gun list with all weapon types, assigns particle emitter
 * presets, and creates animation resources for each gun.
 */
void Gun_Start() {
    // Set up particle emitter presets
    ParticleEmitter* muzzleFlashEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_MuzzleFlash);
    
    GunList[GUN_PISTOL].config.casingPreset = ParticleEmitter_PistolSMGCasing;
    GunList[GUN_SMG].config.casingPreset = ParticleEmitter_PistolSMGCasing;
    GunList[GUN_REVOLVER].config.casingPreset = ParticleEmitter_PistolSMGCasing;
    GunList[GUN_ARMOR_PISTOL].config.casingPreset = ParticleEmitter_PistolSMGCasing;
    GunList[GUN_RAPID_SMG].config.casingPreset = ParticleEmitter_PistolSMGCasing;
    GunList[GUN_PDW].config.casingPreset = ParticleEmitter_PistolSMGCasing;
    GunList[GUN_BURST_RIFLE].config.casingPreset = ParticleEmitter_ARBRCasing;
    GunList[GUN_BULLPUP_RIFLE].config.casingPreset = ParticleEmitter_ARBRCasing;
    GunList[GUN_AUTO_SHOTGUN].config.casingPreset = ParticleEmitter_ShotgunCasing;
    GunList[GUN_ASSAULT_RIFLE].config.casingPreset = ParticleEmitter_ARBRCasing;
    GunList[GUN_BATTLE_RIFLE].config.casingPreset = ParticleEmitter_ARBRCasing;
    GunList[GUN_SHOTGUN].config.casingPreset = ParticleEmitter_ShotgunCasing;


    // Set up resources
    for (int i = 0; i < GUN_COUNT; i++) {
        GunData *gun = &GunList[i];
        gun->type = i;
        gun->resources.bulletFragmentEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_BulletFragments);
        gun->resources.casingParticleEmitter = ParticleEmitter_CreateFromPreset(gun->config.casingPreset);
        gun->resources.muzzleFlashEmitter = muzzleFlashEmitter;
        gun->resources.animation = Animation_Create(&gun->animData);
    }   
    Bullet_Start();
}