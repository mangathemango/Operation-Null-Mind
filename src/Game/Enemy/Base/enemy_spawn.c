#include <enemy.h>
#include <stdlib.h>

void Enemy_Spawn(EnemyData data, Vec2 position) {
    SDL_Log("Spawning enemy at %f, %f", position.x, position.y);
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (!enemies[i].state.isDead) continue;
        SDL_Log("Spawning enemy at index %d", i);
        EnemyData* enemy = &enemies[i];
        memcpy(enemy, &data, sizeof(EnemyData));

        enemy->state.position = position;
        enemy->state.isDead = false;
        enemy->state.currentHealth = enemy->stats.maxHealth;
        enemy->state.collider.hitbox.x = position.x;
        enemy->state.collider.hitbox.y = position.y;

        enemy->resources.animation = Animation_Create(&enemy->animData);
        Collider_Register(&enemy->state.collider, enemy);
        if (enemy->start) enemy->start(enemy);
        break;
    }
}