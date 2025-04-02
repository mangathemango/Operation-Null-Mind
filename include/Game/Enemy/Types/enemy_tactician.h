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
typedef enum {
    TACTICIAN_STATE_WALKING   = 0,
    TACTICIAN_STATE_SHOOTING    = 1 << 0,
    TACTICIAN_STATE_COMMANDING  = 1 << 1,
} TacticianState;

typedef struct {
    float directionChangeTimer;
    float directionChangeTime;
    float shootTime;
    float shootTimer;
    GunData gun;
    Vec2 gunOffset;
    Vec2 lastPosition;
    
    TacticianState state;
    float commandRadius;
    float buffStrength;
    float commandTimer;
    float commandTime;

    float burstTimer;
    float burstTime;
    int currentBurstCount;
    int maxBurstCount;
} TacticianConfig;

void Tactician_Start(EnemyData* data);
void Tactician_Update(EnemyData* data);
void Tactician_Render(EnemyData* data);
void Tactician_UpdateParticles();
void Tactician_RenderParticles();

extern TacticianConfig TacticianConfigData;
extern EnemyData TacticianData;
