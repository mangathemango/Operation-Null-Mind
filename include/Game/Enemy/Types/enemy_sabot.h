/**
 * @file enemy_sabot.h
 * @brief This file contains the data for the Sabot enemy type.
 *
 * @author Mango
 * @date 2025-03-21
 */

#pragma once
#include <enemy.h>

typedef struct {
    float chargeTime;        // Time required to charge before attack
    float chargeSpeed;       // Speed multiplier when charging
    float piercingFactor;    // How much this enemy can pierce defenses
    bool isCharging;         // Flag indicating if enemy is charging
    Vec2 chargeDirection;    // Direction of the charge attack
} SabotConfig;

void Sabot_Start (EnemyData* data);
void Sabot_Update(EnemyData* data);
void Sabot_Render(EnemyData* data);

extern SabotConfig SabotConfigData;
extern EnemyData SabotData;
