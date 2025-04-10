#include <enemy_libet.h>
#include <time_system.h>
#include <particle_emitterpresets.h>
#include <player.h>
#include <random.h>
#include <math.h>
#include <chunks.h>

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
    static int targetHP = 0;
    static int attackCounter = 0;
    static int phase = 0;
    static Vec2 currentLazer = {0, 0};

    config->floatTime = 1.0f - phase * 0.3f;

    switch (config->state) {

    case LIBET_FLOATING:
        // Handle floating behavior
        if (config->timer >= config->floatTime) {
            if (attackCounter >= 10) {
                config->state = LIBET_VINCIBLE;
                targetHP = data->state.currentHealth - 1000;
                attackCounter = 0;
                break;
            }
            
            attackCounter++;
            int randomState; 
            if (EnemyManage_CountEnemyInChunk(Chunk_GetCurrentChunk(data->state.position)) < 2 + phase) {
                if (phase < 2) {
                    randomState = 0;
                } else {
                    randomState = RandInt(0, 1);
                }
            } else {
                randomState = RandInt(2, 3);
                if (phase >= 1) randomState = RandInt(2, 4);
                if (phase >= 3) randomState = RandInt(2, 5);
            }
            switch (randomState) {
                case 0:
                    config->state = LIBET_EXPLOSION_FIRING;
                    break;
                case 1:
                    config->state = LIBET_JUGGERNAUT_SPAMMING;
                    break;
                case 2:
                    config->state = LIBET_DIAGONAL_LAZER_CHARGING;
                    for (int x = -1; x <= 1; x++) {
                        for (int y = -1; y <= 1; y++) {
                            if (x == 0 && y == 0) continue;
                            Vec2 direction = Vec2_Normalize((Vec2){x, y});
                            Lazer lazer = {
                                .active = true,
                                .startPosition = data->state.position,
                                .direction = direction,
                                .width = 0,
                                .damage = 0,
                                .lifeTime = 0.0f
                            };
                            Libet_AddLazer(lazer);
                        }
                    }
                    break;
                case 3:
                    config->state = LIBET_BULLET_HELL_FIRING;
                    break;
                case 4:
                    config->state = LIBET_BIG_LAZER_CHARGING;
                    Vec2 direction = 
                    Vec2_RotateDegrees(
                        Vec2_Normalize(
                            Vec2_Subtract(player.state.position, data->state.position)
                        ), 
                        -90
                    );
                    Lazer lazer = {
                        .active = true,
                        .startPosition = data->state.position,
                        .direction = direction,
                        .width = 0,
                        .damage = 0,
                        .lifeTime = 0.0f
                    };
                    Libet_AddLazer(lazer);
                    break;
                case 5:
                    config->state = LIBET_ROOM_LAZER_FIRING;
                    currentLazer = Vec2_Add(
                        Chunk_GetRoomTopLeft(Chunk_GetCurrentChunk(data->state.position)), 
                        (Vec2) {
                            RandInt(0, 60),
                            RandInt(-10, 50)
                        });
                    break;
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
                libetLazers[i].damage = 10;
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
            if (juggernautCounter >= 5 || EnemyManage_CountEnemyInChunk(Chunk_GetCurrentChunk(data->state.position)) >= 2 + phase) {
                juggernautCounter = 0;
                config->state = LIBET_FLOATING;
                config->timer = 0;
            }
        }
        break;
    
    case LIBET_EXPLOSION_FIRING:
        static int explosionCounter = 0;
        float explosionFireRate = 0.1f;
        static float explosionFireRateTimer = 0.0f;
        explosionFireRateTimer += Time->deltaTimeSeconds;
        if (explosionFireRateTimer >= explosionFireRate) {
            explosionFireRateTimer = 0.0f;
            Vec2 spawnPosition = Chunk_GetRandomTileCenterInRoom(
                Chunk_GetCurrentChunk(player.state.position) // Assuming you have a function to get the current chunk
            );
            Enemy_Spawn(*enemyList[ENEMY_TYPE_KAMIKAZE], spawnPosition);
            explosionCounter++;
            if (explosionCounter >= 5 || EnemyManage_CountEnemyInChunk(Chunk_GetCurrentChunk(data->state.position)) >= 2 + phase * 2) {
                explosionCounter = 0;
                config->state = LIBET_FLOATING;
                config->timer = 0;
            }
        }
        break;

    case LIBET_VINCIBLE:
        Animation_Play(data->resources.animation, "[VINCIBLE]");
        data->state.collider.layer = COLLISION_LAYER_ENEMY;
        if (data->state.currentHealth <= targetHP) {
            config->state = LIBET_FLOATING;
            config->timer = 0;
            phase++;
            Animation_Play(data->resources.animation, "[INVINCIBLE]");
            data->state.collider.layer = COLLISION_LAYER_NONE;
        }
        break;
    
    case LIBET_BIG_LAZER_CHARGING:
        for (int i = 0; i < 40; i++) {
            if (libetLazers[i].active) {
                libetLazers[i].startPosition = data->state.position;
                libetLazers[i].width = 0;
            }
        }
        // Handle big lazer charging behavior
        if (config->timer >= config->lazerChargeTime) {
            config->state = LIBET_BIG_LAZER_FIRING;
            config->timer = 0;
        }
        break;
    
    case LIBET_BIG_LAZER_FIRING:
        for (int i = 0; i < 40; i++) {
            if (libetLazers[i].active) {
                libetLazers[i].startPosition = data->state.position;
                libetLazers[i].direction = Vec2_RotateDegrees(
                    libetLazers[i].direction, 
                    180.0f * (Time->deltaTimeSeconds / 2) // Rotate the lazer direction
                );
                libetLazers[i].width = 5 * sin(config->timer / 2 * M_PI); // Gradually increase width
                libetLazers[i].damage = 10;
            }
        }
        // Handle big lazer firing behavior
        if (config->timer >= 2) {
            for (int i = 0; i < 40; i++) {
                libetLazers[i].active = false;
            }
            config->state = LIBET_FLOATING;
            config->timer = 0;
        }
        break;

    case LIBET_ROOM_LAZER_FIRING:
        for (int i = 0; i < 40; i++) {
            if (libetLazers[i].active) {
                if (libetLazers[i].lifeTime >= 1.7f) {
                    libetLazers[i].width = -1;
                    libetLazers[i].damage = 0;
                    libetLazers[i].active = false;
                    libetLazers[i].lifeTime = 0;
                } else if (libetLazers[i].lifeTime >= 1.5f) {
                    libetLazers[i].width = 5 - (libetLazers[i].lifeTime - 1.5f) * 25;
                    libetLazers[i].damage = 10;
                } else {
                    libetLazers[i].width = 0;
                    libetLazers[i].damage = 0;
                }
            }
        }

        static int fireMode = 0;
        if (config->timer >= 0.1f) {
            if (currentLazer.y <= Chunk_GetRoomBottomRight(Chunk_GetCurrentChunk(data->state.position)).y && fireMode == 0) {
                config->timer = 0;
                Vec2 startPosition = (Vec2) {
                    Chunk_GetRoomTopLeft(Chunk_GetCurrentChunk(data->state.position)).x,
                    currentLazer.y
                };
                Lazer lazer = {
                    .active = true,
                    .startPosition = startPosition,
                    .direction = Vec2_Right,
                    .width = 0,
                    .damage = 0,
                    .lifeTime = 0.0f
                };
                Libet_AddLazer(lazer);
                currentLazer.y += 60;
                break;
            } else if (currentLazer.y >= Chunk_GetRoomTopLeft(Chunk_GetCurrentChunk(data->state.position)).y && fireMode == 0) {
                fireMode = 1;
                break;
            } else if (currentLazer.x <= Chunk_GetRoomBottomRight(Chunk_GetCurrentChunk(data->state.position)).x && fireMode == 1) {
                config->timer = 0;
                Vec2 startPosition = (Vec2) {
                    currentLazer.x,
                    Chunk_GetRoomTopLeft(Chunk_GetCurrentChunk(data->state.position)).y - 20
                };
                Lazer lazer = {
                    .active = true,
                    .startPosition = startPosition,
                    .direction = Vec2_Down,
                    .width = 0,
                    .damage = 0,
                    .lifeTime = 0.0f
                };
                Libet_AddLazer(lazer);
                currentLazer.x += 60;
                break;
            } else {
                fireMode = 0;
                if (config->timer > 2) {
                    config->timer = 0;
                    for (int i = 0; i < 40; i++) {
                        libetLazers[i].active = false;
                    }
                    config->state = LIBET_FLOATING;
                }
                break;
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
                    Player_TakeDamage(10);
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