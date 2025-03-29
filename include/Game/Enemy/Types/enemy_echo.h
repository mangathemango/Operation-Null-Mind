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

typedef struct {
    float directionChangeTimer;
    float directionChangeTime;
    float shootTime;
    float shootTimer;
    GunData gun;
    Vec2 gunOffset;
    Vec2 lastPosition;
    
    // Echo-specific fields
    float echoDelay;     // Time before echoing player movement
    Vec2 echoPosition;   // Position to echo
    bool isEchoing;      // Whether currently echoing
} EchoConfig;

void Echo_Start(EnemyData* data);
void Echo_Update(EnemyData* data);
void Echo_Render(EnemyData* data);
void Echo_UpdateParticles();
void Echo_RenderParticles();

extern EchoConfig EchoConfigData;
extern EnemyData EchoData;