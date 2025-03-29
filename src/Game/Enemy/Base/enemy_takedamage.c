/**
 * @file enemy_takedamage.c
 * @brief Handles enemy damage and health
 *
 * Implements the damage processing system for enemies,
 * including health reduction and death checks.
 *
 * @author Mango
 * @date 2025-03-04
 */

#include <enemy.h>
#include <player.h>

/**
 * @brief [Utility] Applies damage to an enemy
 * 
 * Reduces an enemy's health based on the damage amount. Enemies with
 * 0 or less health after damage will be marked for death processing.
 * 
 * @param enemy Pointer to the enemy to damage
 * @param damage Amount of damage to apply
 */
void Enemy_TakeDamage(EnemyData* enemy, int damage) {
    if (enemy->state.isDead) return;
    
    enemy->state.currentHealth -= (damage * player.stats.crashOutCurrentMultipler);
    SDL_Log("Enemy %s took %f damage, current health: %d", enemy->name, damage * player.stats.crashOutCurrentMultipler, enemy->state.currentHealth);
}