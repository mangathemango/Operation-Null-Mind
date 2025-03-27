/**
 * @file enemy_radius.h
 * @brief This file contains the data for the Radius enemy type.
 *
 * @author Mango
 * @date 2025-03-22
 */

#pragma once
#include <enemy.h>

typedef struct {
    float aoeRadius;         // Radius of area-of-effect attacks
    float explosionDamage;   // Damage of area-of-effect attacks
    float chargeupTime;      // Time to charge up area attack
    bool isCharging;         // Flag indicating if enemy is charging attack
    float currentCharge;     // Current charge level (0.0-1.0)
} RadiusConfig;

void Radius_Start (EnemyData* data);
void Radius_Update(EnemyData* data);
void Radius_Render(EnemyData* data);

extern RadiusConfig RadiusConfigData;
extern EnemyData RadiusData;
