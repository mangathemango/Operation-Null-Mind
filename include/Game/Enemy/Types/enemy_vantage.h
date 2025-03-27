/**
 * @file enemy_vantage.h
 * @brief This file contains the data for the Vantage enemy type.
 *
 * @author Mango
 * @date 2025-03-22
 */

#pragma once
#include <enemy.h>

typedef struct {
    float detectionRange;    // Maximum range at which enemy can detect player
    float sniperRange;       // Optimal firing range
    float aimTime;           // Time required to aim before firing
    bool isAiming;           // Flag indicating if enemy is currently aiming
    Vec2 targetPosition;     // Position enemy is aiming at
} VantageConfig;

void Vantage_Start (EnemyData* data);
void Vantage_Update(EnemyData* data);
void Vantage_Render(EnemyData* data);

extern VantageConfig VantageConfigData;
extern EnemyData VantageData;
