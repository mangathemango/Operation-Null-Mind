#include <enemy.h>

void Enemy_TakeDamage(EnemyData* enemy, int damage) {
    enemy->state.currentHealth -= damage;
}