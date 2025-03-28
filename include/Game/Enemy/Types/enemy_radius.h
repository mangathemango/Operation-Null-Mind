/**
 * @file enemy_radius.h
 * @brief This file contains the data for the Radius enemy type.
 */

#pragma once
#include <enemy.h>
#include <gun.h>

extern ParticleEmitter* RadiusBulletEmitter;
extern ParticleEmitter* RadiusBulletFragmentsEmitter;
extern ParticleEmitter* RadiusMuzzleFlashEmitter;
extern ParticleEmitter* RadiusCasingEmitter;

typedef struct {
    float directionChangeTimer;
    float directionChangeTime;
    float shootTime;
    float shootTimer;
    GunData gun;
    Vec2 gunOffset;
    Vec2 lastPosition;
    
    // Radius-specific fields
    float shotSpreadRadius;
    float orbitDistance;
    bool isOrbiting;
    float orbitSpeed;
    float orbitAngle;
} RadiusConfig;

void Radius_Start(EnemyData* data);
void Radius_Update(EnemyData* data);
void Radius_Render(EnemyData* data);
void Radius_UpdateParticles();
void Radius_RenderParticles();

extern RadiusConfig RadiusConfigData;
extern EnemyData RadiusData;
