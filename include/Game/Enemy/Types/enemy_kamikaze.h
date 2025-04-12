/**
 * @file enemy_kamikaze.h
 * @brief This file contains the data for the enemy **Echo**.
 *
 * @author Mango
 * @date 2025-03-19
 */

#pragma once
#include <enemy.h>
#include <particle_emitterpresets.h>

typedef enum {
    KAMIKAZE_STATE_WALKING,
    KAMIKAZE_STATE_CHARGING,
    KAMIKAZE_STATE_EXPLODING,
} KamikazeState;

typedef struct {
    KamikazeState state;
    float explosionRadius;
    float explosionTime;
    float indicatorDelay;
    float directionChangeTime;
    float explosionTimer;
    float beepTimer;
    SDL_Texture* explosionIndicator;
} KamikazeConfig;
extern ParticleEmitter* KamikazeExplosionEmitter;

void Kamikaze_Start (EnemyData* data);
void Kamikaze_Update(EnemyData* data);
void Kamikaze_Render(EnemyData* data);
void Kamikaze_OnDeath(EnemyData* data);

extern KamikazeConfig KamikazeConfigData;
extern EnemyData KamikazeData;