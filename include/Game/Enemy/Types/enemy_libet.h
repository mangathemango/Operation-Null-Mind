#ifndef ENEMY_LIBET_H
#define ENEMY_LIBET_H

#include <enemy.h>

typedef enum {
    LIBET_FLOATING,
    LIBET_VINCIBLE,
    LIBET_DIAGONAL_LAZER_CHARGING,
    LIBET_DIAGONAL_LAZER_FIRING,
    LIBET_EXPLOSION_FIRING,
    LIBET_ROOM_LAZER_FIRING,
    LIBET_BULLET_HELL_FIRING,
    LIBET_BIG_LAZER_CHARGING,
    LIBET_BIG_LAZER_FIRING,
    LIBET_JUGGERNAUT_SPAMMING,
    LIBET_SPINNING,
} LibetState;

/**
 * @brief Configuration structure for Libet boss enemy
 */
typedef struct {
    LibetState state;           /**< Current state of the Libet enemy */

} LibetConfig;


extern LibetConfig LibetConfigData;
extern EnemyData LibetData;

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

#endif // ENEMY_LIBET_H