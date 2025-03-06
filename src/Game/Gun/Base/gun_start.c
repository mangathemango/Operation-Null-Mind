#include <gun.h>

void Gun_Start() {
    Gun_AnimationInit();
    Gun_Pistol.config.casingParticleEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_PistolSMGCasing);
    Gun_SMG.config.casingParticleEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_PistolSMGCasing);
    Gun_AssaultRifle.config.casingParticleEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_ARBRCasing);
    Gun_BattleRifle.config.casingParticleEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_ARBRCasing);
    Gun_Shotgun.config.casingParticleEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_ShotgunCasing);
}