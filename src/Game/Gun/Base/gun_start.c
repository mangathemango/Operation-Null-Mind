//? Written by Mango on 07/03/2025

#include <gun.h>

/*
*   [Start] Initializes the gun and its particle emitters
*/
void Gun_Start() {
    Gun_AnimationInit();
    Gun_Pistol.resources.casingParticleEmitter =       ParticleEmitter_CreateFromPreset(ParticleEmitter_PistolSMGCasing);
    Gun_SMG.resources.casingParticleEmitter =          ParticleEmitter_CreateFromPreset(ParticleEmitter_PistolSMGCasing);
    Gun_AssaultRifle.resources.casingParticleEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_ARBRCasing);
    Gun_BattleRifle.resources.casingParticleEmitter =  ParticleEmitter_CreateFromPreset(ParticleEmitter_ARBRCasing);
    Gun_Shotgun.resources.casingParticleEmitter =      ParticleEmitter_CreateFromPreset(ParticleEmitter_ShotgunCasing);
    
    ParticleEmitter* muzzleFlashEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_MuzzleFlash);
    Gun_Pistol.resources.muzzleFlashEmitter =          muzzleFlashEmitter;
    Gun_SMG.resources.muzzleFlashEmitter =             muzzleFlashEmitter;
    Gun_AssaultRifle.resources.muzzleFlashEmitter =    muzzleFlashEmitter;
    Gun_BattleRifle.resources.muzzleFlashEmitter =     muzzleFlashEmitter;
    Gun_Shotgun.resources.muzzleFlashEmitter =         muzzleFlashEmitter;
}