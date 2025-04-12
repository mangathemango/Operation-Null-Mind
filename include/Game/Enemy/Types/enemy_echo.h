/**
 * @file enemy_echo.h
 * @brief This file contains the data for the enemy **Echo**.
 *
 * @author Mango
 * @date 2025-03-19
 */

#pragma once
#include <enemy.h>
#include <gun.h>

extern ParticleEmitter* EchoBulletEmitter;
extern ParticleEmitter* EchoBulletFragmentsEmitter;
extern ParticleEmitter* EchoMuzzleFlashEmitter;
extern ParticleEmitter* EchoCasingEmitter;

typedef enum {
    ECHO_STATE_WALKING,
    ECHO_STATE_BURSTING
} EchoState;
typedef struct {
    EchoState state;
    float directionChangeTimer;
    float directionChangeTime;
    float shootTime;
    float shootTimer;
    GunData gun;
    Vec2 gunOffset;
    Vec2 lastPosition;
    
    // Echo-specific fields
    int burstCount;
    int burstMaxCount;
    float burstTimer;
    float burstTime;
} EchoConfig;

void Echo_Start(EnemyData* data);
void Echo_Update(EnemyData* data);
void Echo_UpdateGun(EnemyData* data);
void Echo_Render(EnemyData* data);
void Echo_UpdateParticles();
void Echo_RenderParticles();
void Echo_OnDeath(EnemyData* data);

extern EchoConfig EchoConfigData;
extern EnemyData EchoData;