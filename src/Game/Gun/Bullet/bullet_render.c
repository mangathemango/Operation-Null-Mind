#include <bullet.h>
#include <particle_emitterpresets.h>
#include <player.h>

void Bullet_Render()
{
    GunData* gun = player.state.currentGun;

    ParticleEmitter_Render(gun->resources.bulletPreset);

    ParticleEmitter_Render(gun->resources.bulletFragmentEmitter);
}