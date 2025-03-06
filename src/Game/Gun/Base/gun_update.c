#include <gun.h>
#include <player.h>

void Gun_Update() {
    GunData* gun = player.state.currentGun;
    ParticleEmitter_Update(gun->config.casingParticleEmitter);
    gun->config.casingParticleEmitter->position = player.state.position;
    Gun_AnimationUpdate();
}