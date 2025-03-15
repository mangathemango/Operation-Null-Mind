#include <bullet.h>
#include <particle_emitterpresets.h>
#include <gun.h>
#include <player.h>

void Bullet_Start()
{
     //Set up bullet emitter presets
     ParticleEmitter* bulletEmitter = ParticleEmitter_CreateFromPreset(bullet_Default);

     GunData* gun = player.state.currentGun;
     gun->resources.bulletPreset = bulletEmitter;
}