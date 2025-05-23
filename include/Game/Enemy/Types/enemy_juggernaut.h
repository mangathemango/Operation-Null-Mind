/**
 * @file enemy_juggernaut.h
 * @brief This file contains the data for the Juggernaut enemy type.
 */

#pragma once
#include <enemy.h>
#include <gun.h>

extern ParticleEmitter* JuggernautBulletEmitter;
extern ParticleEmitter* JuggernautBulletFragmentsEmitter;
extern ParticleEmitter* JuggernautMuzzleFlashEmitter;
extern ParticleEmitter* JuggernautCasingEmitter;

typedef enum {
    JUGGERNAUT_STATE_WALKING,
    JUGGERNAUT_STATE_CHARGING,
    JUGGERNAUT_STATE_ENRAGED
} JuggernautState;

typedef struct {
    float directionChangeTimer;
    float directionChangeTime;
    float shootTime;
    float shootTimer;
    GunData gun;
    Vec2 gunOffset;
    Vec2 lastPosition;
    
    // Juggernaut-specific fields
    JuggernautState state;
    float timer;
    float walkDuration;
    float chargeDuration;
    float enragedDuration;
    float spinSpeedDegrees;
} JuggernautConfig;

void Juggernaut_Start(EnemyData* data);
void Juggernaut_Update(EnemyData* data);
void Juggernaut_Render(EnemyData* data);
void Juggernaut_UpdateParticles();
void Juggernaut_RenderParticles();

extern JuggernautConfig JuggernautConfigData;
extern EnemyData JuggernautData;
