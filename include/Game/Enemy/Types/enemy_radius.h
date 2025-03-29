/**
 * @file enemy_radius.h
 * @brief This file contains the data for the Radius enemy type.
 */

#pragma once
#include <enemy.h>
#include <gun.h>
#include <circle.h>

extern ParticleEmitter* RadiusBulletEmitter;
extern ParticleEmitter* RadiusBulletFragmentsEmitter;
extern ParticleEmitter* RadiusMuzzleFlashEmitter;
extern ParticleEmitter* RadiusCasingEmitter;
extern ParticleEmitter* RadiusExplosionEmitter;
extern SDL_Texture* RadiusExplosionIndicator;
typedef struct {
    float directionChangeTimer;
    float directionChangeTime;
    float shootTime;
    float shootTimer;
    GunData gun;
    Vec2 gunOffset;
    Vec2 lastPosition;
    
    // Radius-specific fields
    float explosionRadius;
} RadiusConfig;

void Radius_Start(EnemyData* data);
void Radius_Update(EnemyData* data);
void Radius_Render(EnemyData* data);
void Radius_UpdateParticles();
void Radius_RenderParticles();

extern RadiusConfig RadiusConfigData;
extern EnemyData RadiusData;
