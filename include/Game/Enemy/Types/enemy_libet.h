#pragma once

#include <enemy.h>
#include <lazer_system.h>

typedef enum {
    LIBET_EXPLOSION_FIRING,
    LIBET_JUGGERNAUT_SPAMMING,
    LIBET_DIAGONAL_LAZER_CHARGING,
    LIBET_BULLET_HELL_FIRING,
    LIBET_BIG_LAZER_CHARGING,
    LIBET_ROOM_LAZER_FIRING,
    LIBET_FLOATING,
    LIBET_VINCIBLE,
    LIBET_DIAGONAL_LAZER_FIRING,
    LIBET_BIG_LAZER_FIRING,
    LIBET_SPINNING,
} LibetState;

/**
 * @brief Configuration structure for Libet boss enemy
 */
typedef struct {
    LibetState state;           /**< Current state of the Libet enemy */
    float timer;
    float floatTime;
    float lazerChargeTime;
    float lazerFireTime;
} LibetConfig;



extern Lazer libetLazers[40];
extern LibetConfig LibetConfigData;
extern EnemyData LibetData;
extern ParticleEmitter* LibetBulletEmitter;

/**
 * @brief Initializes the Libet boss enemy
 *
 * @param data Pointer to the enemy data structure
 */
void Libet_Start(EnemyData* data);

/**
 * @brief Updates the Libet boss enemy's state
 *
 * @param data Pointer to the enemy data structure
 */
void Libet_Update(EnemyData* data);

/**
 * @brief Renders the Libet boss enemy
 *
 * @param data Pointer to the enemy data structure
 */
void Libet_Render(EnemyData* data);

void Libet_AddLazer(Lazer lazer);

void Libet_OnDeath(EnemyData* data);

void Enemy_RenderBoss();