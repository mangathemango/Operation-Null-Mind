#include <enemy.h>
#include <enemy_types.h>
#include <app.h>

/**
 * [Data] Global arrays for enemy storage and spawn indicator texture
 */
EnemyData enemies[ENEMY_MAX];
SDL_Texture* Enemy_spawnIndicator = NULL;

/**
 * [Start] Initializes the enemy system.
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