/**
 * @file enemy_start.c
 * @brief Initializes the enemy system
 *
 * Sets up the enemy management system, prepares enemy
 * slots and loads shared enemy resources.
 *
 * @author Mango
 * @date 2025-03-04
 */

#include <enemy.h>
#include <enemy_types.h>
#include <app.h>
#include <circle.h>

/**
 * @brief [Data] Global arrays for enemy storage and spawn indicator texture
 */
EnemyData enemies[ENEMY_MAX];
EnemyData *enemyList[ENEMY_TYPE_COUNT];
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

    // Initialize enemy types
    enemyList[ENEMY_TYPE_ECHO] = &EchoData;
    enemyList[ENEMY_TYPE_KAMIKAZE] = &KamikazeData;
    enemyList[ENEMY_TYPE_RECHARGE] = &RechargeData;
    enemyList[ENEMY_TYPE_PROXY] = &ProxyData;
    enemyList[ENEMY_TYPE_SABOT] = &SabotData;
    enemyList[ENEMY_TYPE_VANTAGE] = &VantageData;
    enemyList[ENEMY_TYPE_TACTICIAN] = &TacticianData;
    enemyList[ENEMY_TYPE_RADIUS] = &RadiusData;
    enemyList[ENEMY_TYPE_JUGGERNAUT] = &JuggernautData;
    enemyList[ENEMY_TYPE_SENTRY] = &SentryData;


    KamikazeConfigData.explosionIndicator = CreateCircleTexture(
        KamikazeConfigData.explosionRadius,
        (SDL_Color){255, 0, 0, 255}
    );

    KamikazeExplosionEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_Explosion);
    
    // Proxy particle emitters
    ProxyBulletEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_BulletEnemy);
    ProxyMuzzleFlashEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_MuzzleFlash);
    ProxyCasingEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_PistolSMGCasing);
    ProxyBulletFragmentsEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_BulletFragments);

    // Sabot particle emitters - simplified to match Proxy's approach
    SabotBulletEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_BulletEnemy);
    SabotMuzzleFlashEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_MuzzleFlash);
    SabotCasingEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_PistolSMGCasing);
    SabotBulletFragmentsEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_BulletFragments);
}