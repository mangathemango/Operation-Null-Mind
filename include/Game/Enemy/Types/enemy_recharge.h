/**
 * @file enemy_recharge.h
 * @brief This file contains the data for the Recharge enemy type.
 *
 * @author Mango
 * @date 2025-03-19
 */

#pragma once
#include <enemy.h>

typedef struct {
    float rechargeTime;      // Time required to recharge energy
    float rechargeRadius;    // Radius of the recharge effect 
    float energyDrainRate;   // Rate at which enemy drains player energy
    bool isRecharging;       // Flag indicating if enemy is currently recharging
} RechargeConfig;

void Recharge_Start (EnemyData* data);
void Recharge_Update(EnemyData* data);
void Recharge_Render(EnemyData* data);

extern RechargeConfig RechargeConfigData;
extern EnemyData RechargeData;