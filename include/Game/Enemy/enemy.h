#pragma once

#include <SDL.h>
#include <vec2.h>
#include <colliders.h>
#include <animation.h>

#define ENEMY_MAX 100

typedef enum {
    ENEMY_TYPE_ZFN,
} EnemyType;

typedef struct {
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;
    Collider collider;
    int currentHealth;
    bool isDead;
} EnemyState;

typedef struct {
    int damage;
    int maxHealth;
    int speed;
    int attackSpeed;
    int attackRange;
    int attackDamage;
    int attackCooldown;
} EnemyStats;

typedef struct {
    Animation* animation;
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

void Enemy_Init();
void Enemy_Update();
void Enemy_Render();
void Enemy_Destroy();

void Enemy_Spawn(EnemyData data, Vec2 position);
void Enemy_TakeDamage(EnemyData* enemy, int damage);
