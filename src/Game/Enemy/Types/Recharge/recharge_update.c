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

/**
 * @brief Gets the direction for the Recharge enemy to move towards
 * Recharge typically moves towards the closest non-recharge enemy detected. 
 * 
 * @param data 
 * @return Vec2 
 */
Vec2 Recharge_GetDirection(EnemyData* data) {
    Vec2 closestEnemy = {0, 0};
    float closestDistance = 9999999.0f;

    // Loop through every enemy in the enemy pool
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (enemies[i].state.isDead || enemies[i].type == ENEMY_TYPE_RECHARGE) {
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

    config->directionChangeTimer += Time->deltaTimeSeconds;
    if (config->directionChangeTimer >= config->directionChangeTime) {
        config->directionChangeTimer = 0;
        config->directionChangeTime = RandFloat(0.5f, 2.0f);
        data->state.direction = Recharge_GetDirection(data);
    }

    if (data->stats.maxSpeed > 0) {
        Animation_Play(data->resources.animation, "walking");
    }

    config->timer += Time->deltaTimeSeconds * data->state.tacticianBuff;

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
            Sound_Play_Effect(SOUND_ENEMY_HEALING);

            for (int i = 0; i < ENEMY_MAX; i++) {
                if (enemies[i].state.isDead) {
                    continue;
                }
                if (Vec2_Distance(enemies[i].state.position, data->state.position) < config->rechargeRadius) {
                    if (enemies[i].type == ENEMY_TYPE_RECHARGE) {
                        Enemy_TakeDamage(&enemies[i], -config->healAmount / 2);
                    } else {
                        Enemy_TakeDamage(&enemies[i], -config->healAmount);
                    }
                    if (enemies[i].state.currentHealth > enemies[i].stats.maxHealth) {
                        enemies[i].state.currentHealth = enemies[i].stats.maxHealth;
                    }
                }
            }
        }
    }

    if (data->stats.maxSpeed > 0) {
        Animation_Play(data->resources.animation, "walking");
    } else {
        Animation_Play(data->resources.animation, "idle");
    }
}