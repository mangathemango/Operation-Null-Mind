//? Written by Mango on 07/03/2025

#include <gun.h>
#include <bullet.h>

/*
*   [Start] Initializes the gun and its particle emitters
*/
void Gun_Start() {
    // Fill the gun list
    GunList[0] = &Gun_Pistol;
    GunList[1] = &Gun_SMG;
    GunList[2] = &Gun_AssaultRifle;
    GunList[3] = &Gun_BattleRifle;
    GunList[4] = &Gun_Shotgun;
    
    // Set up particle emitter presets
    ParticleEmitter* muzzleFlashEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_MuzzleFlash);
    Gun_Pistol.config.casingPreset = ParticleEmitter_PistolSMGCasing;
    Gun_SMG.config.casingPreset = ParticleEmitter_PistolSMGCasing;
    Gun_AssaultRifle.config.casingPreset = ParticleEmitter_ARBRCasing;
    Gun_BattleRifle.config.casingPreset = ParticleEmitter_ARBRCasing;
    Gun_Shotgun.config.casingPreset = ParticleEmitter_ShotgunCasing;

    // Set up resources
    for (int i = 0; i < GUN_COUNT; i++) {
        GunData *gun = GunList[i];
        gun->resources.casingParticleEmitter = ParticleEmitter_CreateFromPreset(gun->config.casingPreset);
        gun->resources.muzzleFlashEmitter = muzzleFlashEmitter;
        gun->resources.animation = Animation_Create(&gun->animData);
        //This is because we need it to be in gundata.
        Bullet_Start();
    }   
}