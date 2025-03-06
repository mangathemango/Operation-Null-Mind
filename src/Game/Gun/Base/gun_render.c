#include <gun.h>
#include <input.h>
#include <player.h>

void Gun_Render() {
    GunData* gun = player.state.currentGun;
    if (gun->state.flip == SDL_FLIP_VERTICAL) {
        ParticleEmitter_Render(player.state.currentGun->config.casingParticleEmitter);
    }
    Animation_Render(gunAnimation, 
                    gun->state.position, 
                    gunAnimData.spriteSize,
                    gun->state.angle,
                    &gun->state.rotationCenter,
                    gun->state.flip);
    
    if (gun->state.flip == SDL_FLIP_NONE) {
        ParticleEmitter_Render(player.state.currentGun->config.casingParticleEmitter);
    }   
    ParticleEmitter_Render(player.state.currentGun->config.muzzleFlashEmitter);
}