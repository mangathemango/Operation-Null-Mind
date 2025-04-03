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

    // Sabot particle emitters
    SabotBulletEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_Gernade);  // Changed from BulletEnemy to Gernade
    SabotMuzzleFlashEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_MuzzleFlash);
    SabotCasingEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_PistolSMGCasing);
    SabotBulletFragmentsEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_BulletFragments);
    SabotExplosionIndicator = CreateCircleTexture(  // Added this
        SabotConfigData.explosionRadius,
        (SDL_Color){255, 0, 0, 255}
    );
    SabotExplosionEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_Explosion);  // Added this
    SabotExplosionEmitter->particleSpeed /= 2;  // Added this
    
    // Vantage particle emitters
    VantageBulletEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_BulletEnemy);
    VantageMuzzleFlashEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_MuzzleFlash);
    VantageCasingEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_PistolSMGCasing);
    VantageBulletFragmentsEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_BulletFragments);
    
    // Tactician particle emitters
    TacticianBulletEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_BulletEnemy);
    TacticianMuzzleFlashEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_MuzzleFlash);
    TacticianCasingEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_PistolSMGCasing);
    TacticianBulletFragmentsEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_BulletFragments);
    
    // Sentry particle emitters
    SentryBulletEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_BulletEnemy);
    SentryMuzzleFlashEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_MuzzleFlash);
    SentryCasingEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_PistolSMGCasing);
    SentryBulletFragmentsEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_BulletFragments);
    
    // Radius particle emitters
    RadiusBulletEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_Gernade);
    RadiusMuzzleFlashEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_MuzzleFlash);
    RadiusCasingEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_PistolSMGCasing);
    RadiusBulletFragmentsEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_BulletFragments);
    RadiusExplosionIndicator = CreateCircleTexture(
        KamikazeConfigData.explosionRadius,
        (SDL_Color){255, 0, 0, 255}
    );
    RadiusExplosionEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_Explosion);
    RadiusExplosionEmitter->particleSpeed /= 2;
    // Juggernaut particle emitters
    JuggernautBulletEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_BulletEnemy);
    JuggernautMuzzleFlashEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_MuzzleFlash);
    JuggernautCasingEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_PistolSMGCasing);
    JuggernautBulletFragmentsEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_BulletFragments);
    
    // Echo particle emitters
    EchoBulletEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_BulletEnemy);
    EchoMuzzleFlashEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_MuzzleFlash);
    EchoCasingEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_PistolSMGCasing);
    EchoBulletFragmentsEmitter = ParticleEmitter_CreateFromPreset(ParticleEmitter_BulletFragments);
}