/**
 * @file enemy.h
 * @brief This file contains the definition of the EnemyData struct and its functions.
 *
 * @author Mango
 * @date 2025-03-18
 */

#pragma once

#include <SDL.h>
#include <vec2.h>
#include <colliders.h>
#include <animation.h>
#include <timer.h>

#define ENEMY_MAX 100

/**
 * @brief Enemy type enumeration
 *
 * Defines the different types of enemies in the game
 */
typedef enum {
    ENEMY_TYPE_ECHO,
    ENEMY_TYPE_KAMIKAZE,
    ENEMY_TYPE_RECHARGE,
    ENEMY_TYPE_PROXY,
    ENEMY_TYPE_SABOT,
    ENEMY_TYPE_VANTAGE,
    ENEMY_TYPE_TACTICIAN,
    ENEMY_TYPE_RADIUS,
    ENEMY_TYPE_JUGGERNAUT,
    ENEMY_TYPE_SENTRY,
} EnemyType;

/**
 * @brief Enemy state structure
 *
 * Contains the current runtime state information for an enemy,
 * including position, movement, collision, and health status
 */
typedef struct {
    Vec2 position;       /**< Current position of the enemy */
    Vec2 velocity;       /**< Current velocity of the enemy */
    Vec2 direction;      /**< Direction the enemy is facing/moving */
    Collider collider;   /**< Collision detection information */
    int currentHealth;   /**< Current health points */
    bool isDead;         /**< Whether the enemy is dead */
    bool isSpawning;     /**< Whether the enemy is in spawning state */
} EnemyState;

/**
 * @brief Enemy statistics structure
 *
 * Contains the configuration values that define an enemy's capabilities
 */
typedef struct {
    int damage;          /**< Base damage enemy can inflict */
    int maxHealth;       /**< Maximum health points */
    float maxSpeed;      /**< Maximum movement speed */
    float acceleration;  /**< Movement acceleration rate */
    float drag;          /**< Movement deceleration/friction */
    int attackSpeed;     /**< Speed of attack execution */
    int attackRange;     /**< Maximum attack range */
    int attackDamage;    /**< Damage inflicted by attacks */
    int attackCooldown;  /**< Time between attacks */
} EnemyStats;

/**
 * @brief Enemy resources structure
 *
 * Contains pointers to runtime resources needed by the enemy
 */
typedef struct {
    Animation* animation; /**< Pointer to enemy's animation */
    Timer* timer;         /**< Pointer to enemy's timer for cooldowns/behaviors */
} EnemyResources;

/**
 * @brief Forward declaration of EnemyData structure
 */
typedef struct EnemyData EnemyData;

/**
 * @brief Enemy data structure
 *
 * Complete definition of an enemy, including type, state, stats, 
 * resources, animation data, and function pointers for behavior
 */
typedef struct EnemyData {
    EnemyType type;                    /**< Type of enemy */
    EnemyState state;                  /**< Current state information */
    EnemyStats stats;                  /**< Stats and capabilities */
    EnemyResources resources;          /**< Pointers to resources */
    AnimationData animData;            /**< Animation configuration */

    void* config;                      /**< Enemy type-specific configuration */
    void (*start)(EnemyData* data);    /**< Initialization function */
    void (*update)(EnemyData* data);   /**< Update logic function */
    void (*render)(EnemyData* data);   /**< Render function */
} EnemyData;

/**
 * @brief Array of enemies
 *
 * Holds all the enemies in the game
 */
extern EnemyData enemies[ENEMY_MAX];

/**
 * @brief Texture for enemy spawn indicator
 */
extern SDL_Texture* Enemy_spawnIndicator;

void Enemy_Init();
void Enemy_Update();
void Enemy_HandleSpawning(EnemyData* enemy);
void Enemy_HandleMovement(EnemyData* enemy);
void Enemy_TryMove(EnemyData* enemy, Vec2 movement);
void Enemy_HandleDeath(EnemyData* enemy);
void EnemyManager_Update();
void Enemy_Render();
void Enemy_Destroy();
void Enemy_Spawn(EnemyData data, Vec2 position);
void Enemy_TakeDamage(EnemyData* enemy, int damage);
