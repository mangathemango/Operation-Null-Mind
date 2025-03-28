/**
 * @file enemy_proxy.h
 * @brief This file contains the data for the Proxy enemy type.
 *
 * @author Mango
 * @date 2025-03-20
 */

#pragma once
#include <enemy.h>
#include <gun.h>

extern ParticleEmitter* ProxyBulletEmitter;
extern ParticleEmitter* ProxyBulletFragmentsEmitter;
extern ParticleEmitter* ProxyMuzzleFlashEmitter;
extern ParticleEmitter* ProxyCasingEmitter;
typedef struct {
    float directionChangeTimer;
    float directionChangeTime;
    GunData gun;
    Vec2 gunOffset;
    Vec2 lastPosition;
} ProxyConfig;

void Proxy_Start (EnemyData* data);
void Proxy_Update(EnemyData* data);
void Proxy_Render(EnemyData* data);
void Proxy_UpdateParticles();
void Proxy_RenderParticles();

extern ProxyConfig ProxyConfigData;
extern EnemyData ProxyData;
