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
    
    // Laser aiming system (copied from Vantage)
    bool aiming;
    float aimTime;
    float aimTimer;
    int lazerWidth;
    bool shooting;
    Vec2 lazerStart;
    Vec2 lazerDirection;
    Vec2 lazerEnd;
} SentryConfig;

void Sentry_Start(EnemyData* data);
void Sentry_Update(EnemyData* data);
void Sentry_Render(EnemyData* data);
void Sentry_UpdateParticles();
void Sentry_RenderParticles();
void Sentry_UpdateGun(EnemyData* data);
void Sentry_UpdateLazer(EnemyData* data);
void Sentry_RenderLaser(EnemyData* data);

extern SentryConfig SentryConfigData;
extern EnemyData SentryData;
