#include <enemy.h>

/**
 * [Utility] Applies damage to an enemy.
 * 
 * Reduces an enemy's health based on the damage amount. Enemies with
 * 0 or less health after damage will be marked for death processing.
 * 
 * @param enemy Pointer to the enemy to damage
 * @param damage Amount of damage to apply
 */
void Enemy_TakeDamage(EnemyData* enemy, int damage) {
    if (enemy->state.isDead) return;
    
    enemy->state.currentHealth -= damage;
}