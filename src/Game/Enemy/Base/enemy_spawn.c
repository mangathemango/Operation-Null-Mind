/**
 * @file enemy_spawn.c
 * @brief Handles enemy spawning and initialization
 *
 * Contains functionality for creating new enemy instances
 * based on templates and positioning them in the game world.
 *
 * @author Mango
 * @date 2025-03-03
 */

#include <enemy.h>
#include <stdlib.h>
#include <maps.h>

/**
 * [Utility] Spawns an enemy of the given type at the specified position.
 * 
 * Creates a new enemy instance based on the provided template and initializes it
 * at the given position. If no position is provided (NULL), a random valid position
 * is chosen.
 * 
 * @param data The enemy data template to use for spawning
 * @param position Position vector for enemy spawn location
 */
void Enemy_Spawn(EnemyData data, Vec2 position) {
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (!enemies[i].state.isDead) continue;
        SDL_Log("Spawning enemy at index %d", i);
        EnemyData* enemy = &enemies[i];
        memcpy(enemy, &data, sizeof(EnemyData));

        enemy->state.position = position;
        enemy->state.isDead = false;
        enemy->state.currentHealth = enemy->stats.maxHealth;
        enemy->state.collider.hitbox.x = position.x - enemy->state.collider.hitbox.w / 2;
        enemy->state.collider.hitbox.y = position.y - enemy->state.collider.hitbox.h / 2;
        enemy->state.isSpawning = true;
        enemy->resources.animation = Animation_Create(&enemy->animData);
        enemy->resources.timer = Timer_Create(1.0f);
        Timer_Start(enemy->resources.timer);
        if (enemy->start) enemy->start(enemy);
        break;
    }
}