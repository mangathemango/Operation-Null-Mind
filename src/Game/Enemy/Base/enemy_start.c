#include <enemy.h>
#include <enemy_types.h>

EnemyData enemies[ENEMY_MAX];

void Enemy_Init() {
    for (int i = 0; i < ENEMY_MAX; i++) {
        enemies[i].state.isDead = true;
    }
}