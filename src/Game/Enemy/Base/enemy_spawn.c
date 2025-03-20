#include <enemy.h>
#include <stdlib.h>
#include <maps.h>

void Enemy_Spawn(EnemyData data, Vec2 position) {
    EnvironmentChunk* chunk = Chunk_GetCurrentChunk(position);
    if (chunk->totalEnemyCount <= 0) return;
    chunk->totalEnemyCount--;
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

        enemy->resources.animation = Animation_Create(&enemy->animData);
        Collider_Register(&enemy->state.collider, enemy);
        ColliderCheckResult result;
        Collider_Check(&enemy->state.collider, &result);
        for (int i = 0; i < result.count; i++) {
            if (result.objects[i]->layer & (COLLISION_LAYER_ENVIRONMENT | COLLISION_LAYER_ENEMY | COLLISION_LAYER_PLAYER)) {
                if (result.objects[i]->owner == enemy) continue;
                enemy->state.isDead = true;
                Collider_Reset(&enemy->state.collider);
                return;
            }
        }
        if (enemy->start) enemy->start(enemy);
        break;
    }
}