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
    float rechargeRadius;    // Radius of the recharge effect 
    bool isRecharging;       // Flag indicating if enemy is currently recharging
    
    int healAmount;
    float rechargeCooldown;
    float rechargeDuration;
    float timer;

    float directionChangeTime;
    float directionChangeTimer;

    Vec2 rechargePosition;
    SDL_Texture* rechargeTexture;
} RechargeConfig;

void Recharge_Start (EnemyData* data);
void Recharge_Update(EnemyData* data);
void Recharge_Render(EnemyData* data);
void Recharge_OnDeath(EnemyData* data);

extern RechargeConfig RechargeConfigData;
extern EnemyData RechargeData;