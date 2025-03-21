#pragma once

#include <SDL.h>
#include <vec2.h>
#include <colliders.h>
#include <animation.h>
#include <timer.h>

#define ENEMY_MAX 100

typedef enum {
    ENEMY_TYPE_ZFN,
    ENEMY_TYPE_ECHO
} EnemyType;

typedef struct {
    Vec2 position;
    Vec2 velocity;
    Vec2 direction;
    Collider collider;
    int currentHealth;
    bool isDead;
    bool isSpawning;
} EnemyState;

typedef struct {
    int damage;
    int maxHealth;
    float maxSpeed;
    float acceleration;
    float drag;
    int attackSpeed;
    int attackRange;
    int attackDamage;
    int attackCooldown;
} EnemyStats;

typedef struct {
    Animation* animation;
    Timer* timer;
} EnemyResources;

typedef struct EnemyData EnemyData;

typedef struct EnemyData {
    EnemyType type;
    EnemyState state;
    EnemyStats stats;
    EnemyResources resources;
    AnimationData animData;

    void* config;
    void (*start)(EnemyData* data);
    void (*update)(EnemyData* data);
    void (*render)(EnemyData* data);
} EnemyData;

extern EnemyData enemies[ENEMY_MAX];
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
