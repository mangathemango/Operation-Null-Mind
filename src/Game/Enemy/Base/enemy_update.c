#include <enemy.h>
#include <enemy_types.h>
#include <time_system.h>

/*
*   [PostUpdate] Updates all active enemies in the game.
*   Skips dead enemies and handles special states like spawning.
*   Processes movement and death conditions for each enemy.
*/
void Enemy_Update() {
    for (int i = 0; i < ENEMY_MAX; i++) {
        EnemyData* enemy = &enemies[i];
        if (enemy->state.isDead) continue;  // Skip processing dead enemies
        if (enemy->state.isSpawning) {
            Enemy_HandleSpawning(enemy);
            continue;
        }
        // Call enemy-specific update function if available
        if (enemy->update) enemy->update(enemy);

        Enemy_HandleMovement(enemy);

        // Check if enemy should die
        if (enemy->state.currentHealth <= 0) Enemy_HandleDeath(enemy);
    }
}

/*
*   [PostUpdate] Manages the spawning process for an enemy.
?   The 1 second delay represents the time between the 
?   appearance of the [+] indicator and the enemy actually spawning.
*   
*   @param enemy Pointer to the enemy being spawned
*/
void Enemy_HandleSpawning(EnemyData* enemy) {
    // Initialize spawn timer if needed
    if (!enemy->resources.timer) {
        enemy->resources.timer = Timer_Create(1.0f);
        Timer_Start(enemy->resources.timer);
    }
    // Wait for spawn timer to finish
    if (!Timer_IsFinished(enemy->resources.timer)) return;

    // Clean up timer and complete spawning
    Timer_Destroy(enemy->resources.timer);
    enemy->resources.timer = NULL;
    enemy->state.isSpawning = false;
    
    // Register collider and check for collisions at spawn point
    Collider_Register(&enemy->state.collider, enemy);
    ColliderCheckResult result;
    Collider_Check(&enemy->state.collider, &result);
    for (int i = 0; i < result.count; i++) {
        if (result.objects[i]->layer & (COLLISION_LAYER_ENVIRONMENT | COLLISION_LAYER_ENEMY | COLLISION_LAYER_PLAYER)) {
            if (result.objects[i]->owner == enemy) continue;
            // Kill enemy if spawning inside another object
            Enemy_HandleDeath(enemy);
            break;
        }
    }
}

/*
*   [PostUpdate] Handles enemy movement physics and velocity calculations.
*   Decomposes velocity into forward and lateral components to apply
*   different physics rules to each, then recombines them.
*   
    @param enemy Pointer to the enemy to move
*/
void Enemy_HandleMovement(EnemyData* enemy) {
    // Decompose the enemy's velocity into forward and lateral components.
    Vec2 forwardDir = enemy->state.direction;
    float forwardSpeed = Vec2_Dot(enemy->state.velocity, forwardDir);
    Vec2 forwardComponent = Vec2_Multiply(forwardDir, forwardSpeed);
    Vec2 lateralComponent = Vec2_Subtract(enemy->state.velocity, forwardComponent);
        
    // Only apply walking acceleration on the forward component if below max speed.
    if (forwardSpeed < enemy->stats.maxSpeed) {
        forwardComponent = Vec2_Add(
            forwardComponent, 
            Vec2_Multiply(forwardDir, enemy->stats.acceleration * Time->deltaTimeSeconds)
        );
    }
    
    // Apply damping to the lateral component so it decays over time.
    float lateralDamping = 0.9f;  // Adjust this value as needed.
    lateralComponent = Vec2_Multiply(lateralComponent, lateralDamping);
    
    // Combine the updated forward and lateral parts.
    enemy->state.velocity = Vec2_Add(forwardComponent, lateralComponent);
    // Apply drag
    Vec2_Decrement(
        &enemy->state.velocity,
        Vec2_Multiply(enemy->state.velocity, enemy->stats.drag * Time->deltaTimeSeconds)
    );
    
    // Move along X and Y axes separately for better collision handling
    Enemy_TryMove(enemy, (Vec2) {
        enemy->state.velocity.x * Time->deltaTimeSeconds,
        0
    });
    Enemy_TryMove(enemy, (Vec2) {
        0,
        enemy->state.velocity.y * Time->deltaTimeSeconds
    });
}

/*
*   [PostUpdate] Attempts to move the enemy by the given vector, checking for collisions.
*   If a collision would occur, the movement is canceled.

    @param enemy Pointer to the enemy to move
    @param movement Vector representing the attempted movement
*/
void Enemy_TryMove(EnemyData* enemy, Vec2 movement) {
    Vec2 newPosition = Vec2_Add(enemy->state.position, movement);
    SDL_Rect oldHitbox = enemy->state.collider.hitbox;
    Vec2 position, size;
    Vec2_FromRect(oldHitbox, &position, &size);
    enemy->state.collider.hitbox = Vec2_ToCenteredRect(newPosition, size);

    // Check for collisions at the new position
    ColliderCheckResult result;
    Collider_Check(&enemy->state.collider, &result);

    // Check if the new position is valid
    for (int i = 0 ; i < result.count; i++) {        
        if (result.objects[i]->layer & (
            COLLISION_LAYER_PLAYER | COLLISION_LAYER_ENVIRONMENT | COLLISION_LAYER_ENEMY
        )) 
        {   
            // Revert to old hitbox if collision detected
            enemy->state.collider.hitbox = oldHitbox;
            return;
        }
    }
    // Apply movement if no collisions
    enemy->state.position = newPosition;
}

/*
*   [PostUpdate] Handles the death of an enemy.
*   Sets health to 0, marks as dead, and removes collision.
* 
    @param enemy Pointer to the enemy that died
*/
void Enemy_HandleDeath(EnemyData* enemy) {
    enemy->state.currentHealth = 0;
    enemy->state.isDead = true;
    Collider_Reset(&enemy->state.collider);
}