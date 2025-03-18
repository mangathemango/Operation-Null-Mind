#include <enemy.h>
#include <enemy_types.h>
void Enemy_Update() {
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (enemies[i].state.isDead) continue;

        enemies[i].state.position = Vec2_Add(enemies[i].state.position, enemies[i].state.velocity);
        enemies[i].state.velocity = Vec2_Add(enemies[i].state.velocity, enemies[i].state.acceleration);
        enemies[i].state.collider.hitbox.x = enemies[i].state.position.x;
        enemies[i].state.collider.hitbox.y = enemies[i].state.position.y;

        if (enemies[i].update) enemies[i].update(&enemies[i]);

        if (enemies[i].state.currentHealth <= 0) {
            enemies[i].state.isDead = true;
            enemies[i].state.currentHealth = 0;
            Collider_Reset(&enemies[i].state.collider);
        }
    }
}