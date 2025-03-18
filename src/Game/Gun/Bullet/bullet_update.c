#include <bullet.h>
#include <gun.h>
#include <player.h>

void Bullet_Update()
{
    GunData* gun = player.state.currentGun;

    gun->resources.bulletPreset->position = gun->resources.muzzleFlashEmitter->position;
    gun->resources.bulletPreset->direction = Vec2_RotateDegrees(Vec2_Right, gun->state.angle);

    ColliderCheckResult result;
    for (int i = 0; i < gun->resources.bulletPreset->maxParticles; i++) {
        Particle* particle = &gun->resources.bulletPreset->particles[i];
        if (!particle->alive) continue;
        Collider_Check(particle->collider, &result)
        
        for (int j = 0; j < result.count; j++)
        {
            if (result.objects[j]->layer & (COLLISION_LAYER_ENVIRONMENT | COLLISION_LAYER_ENEMY))
            {
                // Create bullet fragments
                gun->resources.bulletFragmentEmitter->position = particle->position;
                gun->resources.bulletFragmentEmitter->direction = gun->resources.bulletPreset->direction;
                ParticleEmitter_ActivateOnce(gun->resources.bulletFragmentEmitter);
                
                // Deactivate bullet
                particle->alive = false;
                gun->resources.bulletPreset->readyIndex = i;
                Collider_Reset(particle->collider);
                continue;
            }
        }
        
    }
    ParticleEmitter_Update(gun->resources.bulletPreset);
    ParticleEmitter_Update(gun->resources.bulletFragmentEmitter);

}