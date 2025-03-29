/**
 * @file enemy_vantage.h
 * @brief This file contains the data for the Vantage enemy type.
 *
 * @author Mango
 * @date 2025-03-22
 */

#pragma once
#include <enemy.h>
#include <gun.h>

extern ParticleEmitter* VantageBulletEmitter;
extern ParticleEmitter* VantageBulletFragmentsEmitter;
extern ParticleEmitter* VantageMuzzleFlashEmitter;
extern ParticleEmitter* VantageCasingEmitter;

typedef struct {
    float directionChangeTimer;
    float directionChangeTime;
    float shootTime;
    float shootTimer;
    GunData gun;
    Vec2 gunOffset;
    Vec2 lastPosition;
    
    // Vantage-specific fields - keep original functionality
} VantageConfig;

void Vantage_Start(EnemyData* data);
void Vantage_Update(EnemyData* data);
void Vantage_UpdateGun(EnemyData* data);
void Vantage_Render(EnemyData* data);
void Vantage_UpdateParticles();
void Vantage_RenderParticles();

extern VantageConfig VantageConfigData;
extern EnemyData VantageData;
