#include <gun.h>

/*
*   [Start] Initializes the gun and its particle emitters
*/
void Gun_Start() {
    Gun_AnimationInit();
    Gun_Pistol.config.casingParticleEmitter =       ParticleEmitter_CreateFromPreset(ParticleEmitter_PistolSMGCasing);
    Gun_SMG.config.casingParticleEmitter =          ParticleEmitter_CreateFromPreset(ParticleEmitter_PistolSMGCasing);
    Gun_AssaultRifle.config.casingParticleEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_ARBRCasing);
    Gun_BattleRifle.config.casingParticleEmitter =  ParticleEmitter_CreateFromPreset(ParticleEmitter_ARBRCasing);
    Gun_Shotgun.config.casingParticleEmitter =      ParticleEmitter_CreateFromPreset(ParticleEmitter_ShotgunCasing);
    
    ParticleEmitter* muzzleFlashEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_MuzzleFlash);
    Gun_Pistol.config.muzzleFlashEmitter =          muzzleFlashEmitter;
    Gun_SMG.config.muzzleFlashEmitter =             muzzleFlashEmitter;
    Gun_AssaultRifle.config.muzzleFlashEmitter =    muzzleFlashEmitter;
    Gun_BattleRifle.config.muzzleFlashEmitter =     muzzleFlashEmitter;
    Gun_Shotgun.config.muzzleFlashEmitter =         muzzleFlashEmitter;
}