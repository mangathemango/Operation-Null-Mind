#ifndef ENEMY_LIBET_H
#define ENEMY_LIBET_H

#include <enemy.h>

/**
 * @brief Configuration structure for Libet boss enemy
 */
typedef struct {

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