/**
 * @file enemy_sentry.h
 * @brief This file contains the data for the Sentry enemy type.
 */

#pragma once
#include <enemy.h>
#include <gun.h>

extern ParticleEmitter* SentryBulletEmitter;
extern ParticleEmitter* SentryBulletFragmentsEmitter;
extern ParticleEmitter* SentryMuzzleFlashEmitter;
extern ParticleEmitter* SentryCasingEmitter;

typedef struct {
    float directionChangeTimer;
    float directionChangeTime;
    float shootTime;
    float shootTimer;
    GunData gun;
    Vec2 gunOffset;
    Vec2 lastPosition;
    
    // Sentry-specific fields
    float guardRadius;
    float alertLevel;
    float alertThreshold;
    bool isAlerted;
    Vec2 guardPosition;
} SentryConfig;

void Sentry_Start(EnemyData* data);
void Sentry_Update(EnemyData* data);
void Sentry_Render(EnemyData* data);
void Sentry_UpdateParticles();
void Sentry_RenderParticles();

extern SentryConfig SentryConfigData;
extern EnemyData SentryData;
