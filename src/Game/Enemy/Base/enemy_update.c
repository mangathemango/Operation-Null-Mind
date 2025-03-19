#include <enemy.h>
#include <enemy_types.h>
#include <time_system.h>

void Enemy_Update() {
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (enemies[i].state.isDead) continue;
        if (enemies[i].update) enemies[i].update(&enemies[i]);

        // Decompose the enemy's velocity into forward and lateral components.
        Vec2 forwardDir = enemies[i].state.direction;
        float forwardSpeed = Vec2_Dot(enemies[i].state.velocity, forwardDir);
        Vec2 forwardComponent = Vec2_Multiply(forwardDir, forwardSpeed);
        Vec2 lateralComponent = Vec2_Subtract(enemies[i].state.velocity, forwardComponent);
            
        // Only apply walking acceleration on the forward component if below max speed.
        if (forwardSpeed < enemies[i].stats.maxSpeed) {
            forwardComponent = Vec2_Add(
                forwardComponent, 
                Vec2_Multiply(forwardDir, enemies[i].stats.acceleration)
            );
        }
        
        // Apply damping to the lateral component so it decays over time.
        float lateralDamping = 0.9f;  // Adjust this value as needed.
        lateralComponent = Vec2_Multiply(lateralComponent, lateralDamping);
        
        // Combine the updated forward and lateral parts.
        enemies[i].state.velocity = Vec2_Add(forwardComponent, lateralComponent);

        // Apply drag
        Vec2_Decrement(
            &enemies[i].state.velocity,
            Vec2_Multiply(enemies[i].state.velocity, enemies[i].stats.drag * Time->deltaTimeSeconds)
        );
        enemies[i].state.position = Vec2_Add(enemies[i].state.position, enemies[i].state.velocity);
        enemies[i].state.collider.hitbox.x = enemies[i].state.position.x - enemies[i].animData.spriteSize.x / 2;
        enemies[i].state.collider.hitbox.y = enemies[i].state.position.y - enemies[i].animData.spriteSize.y / 2;

        if (enemies[i].state.currentHealth <= 0) {
            enemies[i].state.isDead = true;
            enemies[i].state.currentHealth = 0;
            Collider_Reset(&enemies[i].state.collider);
        }
    }
}