#include <enemy.h>
#include <enemy_types.h>
#include <time_system.h>

void Enemy_Update() {
    for (int i = 0; i < ENEMY_MAX; i++) {
        if (enemies[i].state.isDead) continue;
        if (enemies[i].state.isSpawning && enemies[i].resources.timer) {
            if (Timer_IsFinished(enemies[i].resources.timer)) {
                Timer_Destroy(enemies[i].resources.timer);
                enemies[i].resources.timer = NULL;
                enemies[i].state.isSpawning = false;
            }
            continue;
        }
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
                Vec2_Multiply(forwardDir, enemies[i].stats.acceleration * Time->deltaTimeSeconds)
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
        
        Enemy_TryMove(&enemies[i], (Vec2) {
            enemies[i].state.velocity.x * Time->deltaTimeSeconds,
            0
        });

        Enemy_TryMove(&enemies[i], (Vec2) {
            0,
            enemies[i].state.velocity.y * Time->deltaTimeSeconds
        });


        if (enemies[i].state.currentHealth <= 0) {
            enemies[i].state.isDead = true;
            enemies[i].state.currentHealth = 0;
            Collider_Reset(&enemies[i].state.collider);
        }
    }
}

void Enemy_TryMove(EnemyData* enemy, Vec2 movement) {
    Vec2 newPosition = Vec2_Add(enemy->state.position, movement);
    SDL_Rect oldHitbox = enemy->state.collider.hitbox;
    Vec2 position, size;
    Vec2_FromRect(oldHitbox, &position, &size);
    enemy->state.collider.hitbox = Vec2_ToCenteredRect(newPosition, size);

    ColliderCheckResult result;
    Collider_Check(&enemy->state.collider, &result);

    // Check if the new position is valid
    for (int i = 0 ; i < result.count; i++) {        
        if (result.objects[i]->layer & (
            COLLISION_LAYER_PLAYER | COLLISION_LAYER_ENVIRONMENT | COLLISION_LAYER_ENEMY
        )) 
        {   
            enemy->state.collider.hitbox = oldHitbox;
            return;
        }
    }
    enemy->state.position = newPosition;
}