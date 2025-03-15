#include <bullet.h>
#include <particle_emitterpresets.h>
#include <gun.h>
#include <player.h>

void Bullet_Start()
{
     //Set up bullet emitter presets
     ParticleEmitter* bulletEmitter = ParticleEmitter_CreateFromPreset(bullet_Default);

     for (int i = 0; i < GUN_COUNT; i++) {
          GunData *gun = GunList[i];
          gun->resources.bulletPreset = bulletEmitter;
     }  
}