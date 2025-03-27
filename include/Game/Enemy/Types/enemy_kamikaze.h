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

typedef struct {
    bool exploding;
    float explosionRadius;
    float explosionTime;
    float indicatorDelay;
    float directionChangeTime;
    float explosionTimer;

    SDL_Texture* explosionIndicator;
} KamikazeConfig;
extern ParticleEmitter* KamikazeExplosionEmitter;

void Kamikaze_Start (EnemyData* data);
void Kamikaze_Update(EnemyData* data);
void Kamikaze_Render(EnemyData* data);

extern KamikazeConfig KamikazeConfigData;
extern EnemyData KamikazeData;