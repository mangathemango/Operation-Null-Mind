#include <bullet.h>
#include <gun.h>
#include <player.h>

void Bullet_Update()
{
    GunData* gun = player.state.currentGun;

    gun->resources.bulletPreset->position = gun->resources.muzzleFlashEmitter->position;
    gun->resources.bulletPreset->direction = Vec2_RotateDegrees(Vec2_Right, gun->state.angle);
    ParticleEmitter_Update(gun->resources.bulletPreset);
    Particle_Collision(gun->resources.bulletPreset);
}