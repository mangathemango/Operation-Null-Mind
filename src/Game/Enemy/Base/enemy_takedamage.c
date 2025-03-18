#include <enemy.h>

void Enemy_TakeDamage(EnemyData* enemy, int damage) {
    enemy->state.currentHealth -= damage;
    SDL_Log("Enemy took %d damage. Current health: %d", damage, enemy->state.currentHealth);
}