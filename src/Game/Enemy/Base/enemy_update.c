/**
 * @file enemy_update.c
 * @brief Core enemy update system
 *
 * Manages updates for all active enemies, handling state changes,
 * movement physics, collision detection, and AI activation.
 *
 * @author Mango
 * @date 2025-03-05
 */

#include <player.h>
#include <random.h>
#include <enemy.h>
#include <enemy_types.h>
#include <time_system.h>

/**
 * @brief [PostUpdate] Updates all active enemies in the game.
 * 
 * Main update loop for all enemies in the game. Skips dead enemies,
 * handles special states like spawning, and processes movement and death
 * conditions for each enemy.
 */
void Enemy_Update() {
    ParticleEmitter_Render(TacticianBuffEffectEmitter);
    for (int i = 0; i < ENEMY_MAX; i++) {
        EnemyData* enemy = &enemies[i];
        if (enemy->state.isDead) continue;  // Skip processing dead enemies
        if (enemy->state.isSpawning) {
            Enemy_HandleSpawning(enemy);
            continue;
        }
        enemy->state.flip = enemy->state.direction.x > 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
        // Call enemy-specific update function if available
        if (enemy->update) enemy->update(enemy);
        if (enemy->state.isDead) continue;
        if (enemy->state.tacticianBuffTimeLeft > 0) {
            TacticianBuffEffectEmitter->position = enemy->state.position;
            ParticleEmitter_ActivateOnce(TacticianBuffEffectEmitter);
            enemy->state.tacticianBuffTimeLeft -= Time->deltaTimeSeconds;
        } else {
            enemy->state.tacticianBuff = 1.0f;
            enemy->state.tacticianBuffTimeLeft = 0;
        }
        Enemy_HandleMovement(enemy);
        Animation_Update(enemy->resources.animation);

        // Check if enemy should die
        if (enemy->state.currentHealth <= 0) Enemy_HandleDeath(enemy);
    }
    Enemy_UpdateHealthTexts();
    if (KamikazeExplosionEmitter) ParticleEmitter_Update(KamikazeExplosionEmitter);
    Proxy_UpdateParticles();
    Sabot_UpdateParticles();
    Vantage_UpdateParticles();
    Tactician_UpdateParticles();
    Sentry_UpdateParticles();
    Radius_UpdateParticles();
    Juggernaut_UpdateParticles();
    Echo_UpdateParticles();  // Add Echo particles update
}

/**
 * @brief [Utility] Manages the spawning process for an enemy.
 * 
 * Handles the 1-second delay between the appearance of the [+] indicator
 * and the enemy actually spawning. Also checks for collision at spawn point.
 * 
 * @param enemy Pointer to the enemy being spawned
 */
void Enemy_HandleSpawning(EnemyData* enemy) {
    // Initialize spawn timer if needed
    if (!enemy->resources.timer) {
        enemy->resources.timer = Timer_Create(1.0f);
        Timer_Start(enemy->resources.timer);
    }
    // Wait for spawn timer to finish
    if (!Timer_IsFinished(enemy->resources.timer)) return;

    /**
     * @todo [enemy_update.c:62] Play spawn sfx here
     */

    Sound_Play_Effect(SOUND_SPAWN_IN);
    // Clean up timer and complete spawning
    Timer_Destroy(enemy->resources.timer);
    enemy->resources.timer = NULL;
    enemy->state.isSpawning = false;
    
    // Register collider and check for collisions at spawn point
    Collider_Register(&enemy->state.collider, enemy);
    ColliderCheckResult result;
    Collider_Check(&enemy->state.collider, &result);
    for (int i = 0; i < result.count; i++) {
        if (result.objects[i]->layer & COLLISION_LAYER_PLAYER) {
            // Kill player if spawning inside another object
            Player_TakeDamage(75);
            break;
        }
        if (result.objects[i]->layer & (COLLISION_LAYER_ENVIRONMENT | COLLISION_LAYER_ENEMY | COLLISION_LAYER_PLAYER)) {
            if (result.objects[i]->owner == enemy) continue;
            // Kill enemy if spawning inside another object
            Enemy_HandleDeath(enemy);
            break;
        }
    }
}

/**
 * @brief [Utility] Handles enemy movement physics and velocity calculations.
 * 
 * Implements a complex movement system that decomposes velocity into 
 * forward and lateral components to apply different physics rules to each,
 * then recombines them.
 * 
 * @param enemy Pointer to the enemy to move
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

/**
 * @brief [Utility] Attempts to move the enemy by the given vector, checking for collisions.
 * 
 * Tries to move an enemy to a new position but cancels the movement if 
 * a collision would occur with walls, the player, or other enemies.
 * 
 * @param enemy Pointer to the enemy to move
 * @param movement Vector representing the attempted movement
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

/**
 * @brief [Utility] Handles the death of an enemy.
 * 
 * Sets health to 0, marks as dead, and removes collision.
 * Called when an enemy's health reaches zero or when they spawn inside
 * another object.
 * 
 * @param enemy Pointer to the enemy that died
 */
void Enemy_HandleDeath(EnemyData* enemy) {
    if (enemy->state.isDead) return;
    enemy->state.currentHealth = 0;
    enemy->state.isDead = true;
    Collider_Reset(&enemy->state.collider);
    if (enemy->config) free(enemy->config);
    enemy->config = NULL;
    player.state.currentAmmo += 20 + player.resources.skillResources.scavengerAmmoBonus;

    player.stats.enemiesKilled++;
    if (player.state.currentAmmo > player.stats.maxAmmo) {
        player.state.currentAmmo = player.stats.maxAmmo;
    }
    
}