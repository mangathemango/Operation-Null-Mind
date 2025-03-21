#include <bullet.h>
#include <gun.h>
#include <player.h>
#include <enemy.h>

/**
 * @brief [PostUpdate] Updates all active bullets, handling movement and collisions
 */
void Bullet_Update()
{
    GunData* gun = player.state.currentGun;

    gun->resources.bulletPreset->emissionNumber = gun->stats.bulletsPerShot;
    gun->resources.bulletPreset->particleLifetime = gun->stats.bulletLifetime;
    gun->resources.bulletPreset->angleRange = gun->stats.spread_angle;
    gun->resources.bulletPreset->position = gun->resources.muzzleFlashEmitter->position;
    gun->resources.bulletPreset->direction = Vec2_RotateDegrees(Vec2_Right, gun->state.angle);

    ColliderCheckResult result;

    // Loop through every bullets of the gun
    for (int i = 0; i < gun->resources.bulletPreset->maxParticles; i++) {
        Particle* bullet = &gun->resources.bulletPreset->particles[i];
        if (!bullet->alive) continue;
        
        // Handle collisions
        Collider_Check(bullet->collider, &result);
        for (int j = 0; j < result.count; j++)
        {   
            // Handle dealing damage to enemies
            if (result.objects[j]->layer & COLLISION_LAYER_ENEMY) {
                EnemyData* enemy = (EnemyData*) result.objects[j]->owner;
                Enemy_TakeDamage(enemy, 10);
                Vec2_Increment(&enemy->state.velocity, Vec2_Multiply(bullet->direction, 70));
            }

            // Handle bullet getting destroyed (i.e colliding with walls/enemies)
            if (result.objects[j]->layer & (COLLISION_LAYER_ENVIRONMENT | COLLISION_LAYER_ENEMY))
            {
                // Create bullet fragments
                gun->resources.bulletFragmentEmitter->position = bullet->position;
                gun->resources.bulletFragmentEmitter->direction = gun->resources.bulletPreset->direction;
                ParticleEmitter_ActivateOnce(gun->resources.bulletFragmentEmitter);

                // Deactivate bullet
                bullet->alive = false;
                gun->resources.bulletPreset->readyIndex = i;
                Collider_Reset(bullet->collider);
                break;
            }
        }
        
    }

    // Update particles
    ParticleEmitter_Update(gun->resources.bulletPreset);
    ParticleEmitter_Update(gun->resources.bulletFragmentEmitter);
}