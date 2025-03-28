/**
 * @file enemy_tactician.h
 * @brief This file contains the data for the Tactician enemy type.
 */

#pragma once
#include <enemy.h>
#include <gun.h>

extern ParticleEmitter* TacticianBulletEmitter;
extern ParticleEmitter* TacticianBulletFragmentsEmitter;
extern ParticleEmitter* TacticianMuzzleFlashEmitter;
extern ParticleEmitter* TacticianCasingEmitter;

typedef struct {
    float directionChangeTimer;
    float directionChangeTime;
    float shootTime;
    float shootTimer;
    GunData gun;
    Vec2 gunOffset;
    Vec2 lastPosition;
    
    // Tactician-specific fields
    float commandRadius;
    float buffStrength;
    int maxControlledUnits;
    bool isCommanding;
    int controlledUnitCount;
} TacticianConfig;

void Tactician_Start(EnemyData* data);
void Tactician_Update(EnemyData* data);
void Tactician_Render(EnemyData* data);
void Tactician_UpdateParticles();
void Tactician_RenderParticles();

extern TacticianConfig TacticianConfigData;
extern EnemyData TacticianData;
