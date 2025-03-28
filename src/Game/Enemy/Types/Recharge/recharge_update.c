/**
 * @file recharge_update.c
 * @brief Implements update logic for Recharge enemy type
 *
 * Contains the AI behavior and state updates for the Recharge enemy.
 *
 * @author Mango
 * @date 2025-03-06
 */

#include <enemy_recharge.h>
#include <player.h>
#include <time_system.h>
#include <random.h>
#include <circle.h>

Vec2 Recharge_GetDirection(EnemyData* data) {
    Vec2 closestEnemy = {0, 0};
    float closestDistance = 9999999.0f;

    for (int i = 0; i < ENEMY_MAX; i++) {
        if (enemies[i].state.isDead || &enemies[i] == data) {
            continue;
        }
        float distance = Vec2_Distance(enemies[i].state.position, data->state.position);
        if (distance < closestDistance) {
            closestDistance = distance;
            closestEnemy = enemies[i].state.position;
        }
    }
    if (closestDistance == 9999999.0f) {
        return Vec2_RotateDegrees(Vec2_Up, RandFloat(-180, 180));
    }
    Vec2 targetDirection = Vec2_Normalize(Vec2_Subtract(closestEnemy, data->state.position));

    return Vec2_RotateDegrees(targetDirection, RandFloat(-45, 45));
}

/**
 * @brief [PostUpdate] Updates the Recharge enemy's state
 * 
 * This function is called each frame to update the Recharge enemy's behavior.
 * 
 * @param data Pointer to the enemy data structure
 */
void Recharge_Update(EnemyData* data) {
    RechargeConfig* config = (RechargeConfig*)data->config;
    
    config->timer += Time->deltaTimeSeconds;

    if (config->isRecharging) {
        if (config->timer >= config->rechargeDuration) {
            config->rechargeCooldown = RandFloat(1.0f, 3.0f);
            config->isRecharging = false;
            config->timer = 0;
        }
    } else {
        if (config->timer >= config->rechargeCooldown) {
            config->isRecharging = true;
            config->timer = 0;
            config->rechargePosition = data->state.position;

            for (int i = 0; i < ENEMY_MAX; i++) {
                if (enemies[i].state.isDead) {
                    continue;
                }
                if (Vec2_Distance(enemies[i].state.position, data->state.position) < config->rechargeRadius) {
                    if (enemies[i].type == ENEMY_TYPE_RECHARGE) {
                        enemies[i].state.currentHealth += config->healAmount / 2;
                    } else {
                        enemies[i].state.currentHealth += config->healAmount;
                    }
                    if (enemies[i].state.currentHealth > enemies[i].stats.maxHealth) {
                        enemies[i].state.currentHealth = enemies[i].stats.maxHealth;
                    }
                }
            }
        }
    }

    config->directionChangeTimer += Time->deltaTimeSeconds;
    if (config->directionChangeTimer >= config->directionChangeTime) {
        config->directionChangeTimer = 0;
        config->directionChangeTime = RandFloat(0.5f, 2.0f);
        data->state.direction = Recharge_GetDirection(data);
    }
}