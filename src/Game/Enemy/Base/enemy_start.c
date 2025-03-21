/**
 * @file enemy_start.c
 * @brief Initializes the enemy system
 *
 * Sets up the enemy management system, prepares enemy
 * slots and loads shared enemy resources.
 *
 * @author Mango
 * @date 2025-03-03
 */

#include <enemy.h>
#include <enemy_types.h>
#include <app.h>

/**
 * @brief [Data] Global arrays for enemy storage and spawn indicator texture
 */
EnemyData enemies[ENEMY_MAX];
SDL_Texture* Enemy_spawnIndicator = NULL;

/**
 * @brief [Start] Initializes the enemy system
 * 
 * Prepares all enemy slots as inactive and loads necessary textures.
 */
void Enemy_Init() {
    for (int i = 0; i < ENEMY_MAX; i++) {
        enemies[i].state.isDead = true;
    }
    
    Enemy_spawnIndicator = IMG_LoadTexture(app.resources.renderer, 
        "Assets/Images/Tiles/enemy-spawn-indicator.png");
    
    if (!Enemy_spawnIndicator) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, 
            "Failed to load enemy spawn indicator texture: %s", IMG_GetError());
    }
}