#include <enemy_libet.h>
#include <time_system.h>
#include <particle_emitterpresets.h>
#include <player.h>
#include <random.h>

/**
 * @brief [Update] Updates the Libet boss enemy's state
 *
 * This function is called each frame to update the Libet boss enemy's behavior.
 *
 * @param data Pointer to the enemy data structure
 */
void Libet_Update(EnemyData* data) {
    LibetConfig* config = (LibetConfig*)data->config;
    config->timer += Time->deltaTimeSeconds;
    switch (config->state) {

    case LIBET_FLOATING:
        // Handle floating behavior
        if (config->timer >= config->floatTime) {
            int randomState = RandInt(0, 2); 
            if (randomState == 0) {
                config->state = LIBET_DIAGONAL_LAZER_CHARGING;
                for (int x = -1; x <= 1; x++) {
                    for (int y = -1; y <= 1; y++) {
                        if (x == 0 && y == 0) continue;
                        Vec2 direction = Vec2_Normalize((Vec2){x, y});
                        Lazer lazer = {
                            .active = true,
                            .startPosition = data->state.position,
                            .direction = direction,
                            .width = 5,
                            .damage = 0,
                            .lifeTime = 0.0f
                        };
                        Libet_AddLazer(lazer);
                    }
                }
            } else if (randomState == 1) {
                config->state = LIBET_BULLET_HELL_FIRING;
            } else {
                if (EnemyManage_CountEnemyInChunk(Chunk_GetCurrentChunk(data->state.position)) < 5) {
                    config->state = LIBET_JUGGERNAUT_SPAMMING;
                } else {
                    config->state = LIBET_FLOATING;
                }
            }
            config->timer = 0;
        }
        break;

    case LIBET_DIAGONAL_LAZER_CHARGING:
        for (int i = 0; i < 40; i++) {
            if (libetLazers[i].active) {
                libetLazers[i].startPosition = data->state.position;
                libetLazers[i].width = 0;
            }
        }
        // Handle diagonal lazer charging behavior
        if (config->timer >= config->lazerChargeTime) {
            config->state = LIBET_DIAGONAL_LAZER_FIRING;
            config->timer = 0;
        }
        break;
    
    case LIBET_DIAGONAL_LAZER_FIRING:
        // Handle diagonal lazer firing behavior
        for (int i = 0; i < 40; i++) {
            if (libetLazers[i].active) {
                libetLazers[i].startPosition = data->state.position;
                libetLazers[i].width = 5 - config->timer / config->lazerFireTime * 5;
                libetLazers[i].damage = 20;
            }
        }
        if (config->timer >= config->lazerFireTime) {
            for (int i = 0; i < 40; i++) {
                libetLazers[i].active = false;
            }
            config->state = LIBET_FLOATING;
            config->timer = 0;
        }
        break;
    
    case LIBET_BULLET_HELL_FIRING:
        // Handle bullet hell firing behavior
        LibetBulletEmitter->position = data->state.position;
        LibetBulletEmitter->angleRange = 360;
        LibetBulletEmitter->emissionNumber = 5;

        static int bulletHellCounter = 0;
        static float fireRate = 0.2f;
        static float fireRateTimer = 0.0f;
        fireRateTimer += Time->deltaTimeSeconds;
        if (fireRateTimer >= fireRate) {
            fireRateTimer = 0.0f;
            bulletHellCounter++;
            ParticleEmitter_ActivateOnce(LibetBulletEmitter);
            if (bulletHellCounter >= 20) {
                bulletHellCounter = 0;
                config->state = LIBET_FLOATING;
                config->timer = 0;
            }
        }
        break;
    
    case LIBET_JUGGERNAUT_SPAMMING:
        SDL_Log("Libet is spamming Juggernauts!");
        static int juggernautCounter = 0;
        float juggernautFireRate = 0.3f;
        static float juggernautFireRateTimer = 0.0f;
        juggernautFireRateTimer += Time->deltaTimeSeconds;
        if (juggernautFireRateTimer >= juggernautFireRate) {
            juggernautFireRateTimer = 0.0f;
            Vec2 spawnPosition = Chunk_GetRandomTileCenterInRoom(
                Chunk_GetCurrentChunk(player.state.position) // Assuming you have a function to get the current chunk
            );
            Enemy_Spawn(*enemyList[ENEMY_TYPE_JUGGERNAUT], spawnPosition);
            juggernautCounter++;
            SDL_Log("Juggernaut spawned at %f, %f", spawnPosition.x, spawnPosition.y);
            if (juggernautCounter >= 5) {
                juggernautCounter = 0;
                config->state = LIBET_FLOATING;
                config->timer = 0;
            }
        }
        break;

    
    default:
        config->state = LIBET_FLOATING;
        break;
    }
    for (int i = 0; i < 40; i++) {
        if (libetLazers[i].active) {
            Lazer_Update(&libetLazers[i]);
        }
    }

    // Update bullet emitter
    if (LibetBulletEmitter) {
        LibetBulletEmitter->position = data->state.position;
        ParticleEmitter_Update(LibetBulletEmitter);
        for (int i = 0; i < LibetBulletEmitter->maxParticles; i++) {
            Particle* bullet = &LibetBulletEmitter->particles[i];
            if (!bullet->alive) continue;
            ColliderCheckResult result;
            Collider_Check(bullet->collider, &result);
            for (int j = 0; j < result.count; j++) {
                if (result.objects[j]->layer & COLLISION_LAYER_PLAYER) {
                    Player_TakeDamage(data->stats.damage);
                }
                if (result.objects[j]->layer & (COLLISION_LAYER_ENVIRONMENT | COLLISION_LAYER_PLAYER)) {
                    bullet->alive = false;
                    break;
                }
            }
        }
    }
}

void Libet_AddLazer(Lazer lazer) {
    for (int i = 0; i < 40; i++) {
        if (!libetLazers[i].active) {
            libetLazers[i] = lazer;
            libetLazers[i].active = true;
            break;
        }
    }
}