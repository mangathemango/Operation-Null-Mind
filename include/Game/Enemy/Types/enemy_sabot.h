/**
 * @file enemy_sabot.h
 * @brief This file contains the data for the Sabot enemy type.
 *
 * @author Mango
 * @date 2025-03-21
 */

#pragma once
#include <enemy.h>
#include <gun.h>

extern ParticleEmitter* SabotBulletEmitter;
extern ParticleEmitter* SabotBulletFragmentsEmitter;
extern ParticleEmitter* SabotMuzzleFlashEmitter;
extern ParticleEmitter* SabotCasingEmitter;

typedef struct {
    float directionChangeTimer;
    float directionChangeTime;

    float shootTime;
    float shootTimer;
    GunData gun;
    Vec2 gunOffset;
    Vec2 lastPosition;
} SabotConfig;

void Sabot_Start (EnemyData* data);
void Sabot_Update(EnemyData* data);
void Sabot_Render(EnemyData* data);
void Sabot_UpdateParticles();
void Sabot_RenderParticles();

extern SabotConfig SabotConfigData;
extern EnemyData SabotData;
