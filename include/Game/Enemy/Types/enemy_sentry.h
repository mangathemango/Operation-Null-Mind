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

typedef enum {
    SENTRY_STATE_IDLE,
    SENTRY_STATE_AIMING,
    SENTRY_STATE_SHOOTING,
} SentryState;
typedef struct {
    float directionChangeTimer;
    float directionChangeTime;
    float shootTime;
    float shootTimer;
    GunData gun;
    Vec2 gunOffset;
    Vec2 lastPosition;
    
    // Laser aiming system (copied from Vantage)
    SentryState state;

    float timer;


    float idleTime;
    float aimTime;
    float shootAngleSpeed;
    float shootAngle;

    float lazerWidth;
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
