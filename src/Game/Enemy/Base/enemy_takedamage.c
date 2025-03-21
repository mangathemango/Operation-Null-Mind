#include <enemy.h>

/**
 * [Utility] Applies damage to an enemy.
 * 
 * Reduces an enemy's health based on the damage amount. Enemies with
 * 0 or less health after damage will be marked for death processing.
 * 
 * @param enemy Pointer to the enemy to damage
 * @param damage Amount of damage to apply
 * @return True if the enemy died from this damage, false otherwise
 */
bool Enemy_TakeDamage(EnemyData* enemy, int damage) {
    if (enemy->state.isDead) return false;
    
    enemy->state.currentHealth -= damage;
    
    if (enemy->state.currentHealth <= 0) {
        enemy->state.currentHealth = 0;
        return true;
    }
    
    return false;
}