#include <enemy.h>
#include <player.h>
#include <stdlib.h>

/**
 * @brief [Utility] Handles the death of an enemy.
 * 
 * Sets health to 0, marks as dead, and removes collision.
 * Called when an enemy's health reaches zero or when they spawn inside
 * another object.
 * 
 * @param enemy Pointer to the enemy that died
 */
void Enemy_OnDeath(EnemyData* enemy) {
    if (enemy->state.isDead) return;
    enemy->state.currentHealth = 0;
    enemy->state.isDead = true;
    Collider_Reset(&enemy->state.collider);

    if (enemy->onDeath) enemy->onDeath(enemy);

    player.stats.enemiesKilled++;
    player.state.currentAmmo += 20 + player.resources.skillResources.scavengerAmmoBonus;

    if (player.state.currentAmmo > player.stats.maxAmmo) {
        player.state.currentAmmo = player.stats.maxAmmo;
    }
}