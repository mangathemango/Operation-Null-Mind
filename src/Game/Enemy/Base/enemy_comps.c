#include <enemy.h> 

EnemyComp EnemyComps[20] = {
    // Stage 1 (min 10 max 15)
    {
        .spawnData = {
            {.type = ENEMY_TYPE_PROXY, .maxSpawnCount = 15, .spawnCount = 0},
            {.type = ENEMY_TYPE_ECHO, .maxSpawnCount = 6, .spawnCount = 0}
        },
        .enemyTypeCount = 2,
        .enemyMinSpawnCount = 10,
        .enemyMaxSpawnCount = 15
    },
    
    // Stage 2 (min 12 max 20)
    {
        .spawnData = {
            {.type = ENEMY_TYPE_PROXY, .maxSpawnCount = 20, .spawnCount = 0},
            {.type = ENEMY_TYPE_ECHO, .maxSpawnCount = 9, .spawnCount = 0},
            {.type = ENEMY_TYPE_KAMIKAZE, .maxSpawnCount = 8, .spawnCount = 0}
        },
        .enemyTypeCount = 3,
        .enemyMinSpawnCount = 12,
        .enemyMaxSpawnCount = 20
    },
    
    // Stage 3 (min 15 max 20)
    {
        .spawnData = {
            {.type = ENEMY_TYPE_VANTAGE, .maxSpawnCount = 8, .spawnCount = 0},
            {.type = ENEMY_TYPE_RECHARGE, .maxSpawnCount = 4, .spawnCount = 0},
            {.type = ENEMY_TYPE_KAMIKAZE, .maxSpawnCount = 15, .spawnCount = 0}
        },
        .enemyTypeCount = 3,
        .enemyMinSpawnCount = 15,
        .enemyMaxSpawnCount = 20
    },
    
    // Stage 4 (min 15 max 25)
    {
        .spawnData = {
            {.type = ENEMY_TYPE_ECHO, .maxSpawnCount = 12, .spawnCount = 0},
            {.type = ENEMY_TYPE_VANTAGE, .maxSpawnCount = 10, .spawnCount = 0},
            {.type = ENEMY_TYPE_TACTICIAN, .maxSpawnCount = 5, .spawnCount = 0}
        },
        .enemyTypeCount = 3,
        .enemyMinSpawnCount = 15,
        .enemyMaxSpawnCount = 25
    },
    
    // Stage 5 (min 18 max 30)
    {
        .spawnData = {
            {.type = ENEMY_TYPE_ECHO, .maxSpawnCount = 15, .spawnCount = 0},
            {.type = ENEMY_TYPE_PROXY, .maxSpawnCount = 20, .spawnCount = 0},
            {.type = ENEMY_TYPE_TACTICIAN, .maxSpawnCount = 7, .spawnCount = 0},
            {.type = ENEMY_TYPE_SABOT, .maxSpawnCount = 5, .spawnCount = 0},
            {.type = ENEMY_TYPE_KAMIKAZE, .maxSpawnCount = 15, .spawnCount = 0}
        },
        .enemyTypeCount = 5,
        .enemyMinSpawnCount = 18,
        .enemyMaxSpawnCount = 30
    },
    
    // Stage 6 (min 15 max 20)
    {
        .spawnData = {
            {.type = ENEMY_TYPE_RADIUS, .maxSpawnCount = 10, .spawnCount = 0},
            {.type = ENEMY_TYPE_TACTICIAN, .maxSpawnCount = 5, .spawnCount = 0},
            {.type = ENEMY_TYPE_SABOT, .maxSpawnCount = 10, .spawnCount = 0},
            {.type = ENEMY_TYPE_RECHARGE, .maxSpawnCount = 5, .spawnCount = 0}
        },
        .enemyTypeCount = 4,
        .enemyMinSpawnCount = 15,
        .enemyMaxSpawnCount = 20
    },
    
    // Stage 7 (min 20 max 25)
    {
        .spawnData = {
            {.type = ENEMY_TYPE_SENTRY, .maxSpawnCount = 4, .spawnCount = 0},
            {.type = ENEMY_TYPE_RECHARGE, .maxSpawnCount = 5, .spawnCount = 0},
            {.type = ENEMY_TYPE_RADIUS, .maxSpawnCount = 7, .spawnCount = 0},
            {.type = ENEMY_TYPE_KAMIKAZE, .maxSpawnCount = 20, .spawnCount = 0}
        },
        .enemyTypeCount = 4,
        .enemyMinSpawnCount = 20,
        .enemyMaxSpawnCount = 25
    },
    
    // Stage 8 (min 12 max 15)
    {
        .spawnData = {
            {.type = ENEMY_TYPE_JUGGERNAUT, .maxSpawnCount = 3, .spawnCount = 0},
            {.type = ENEMY_TYPE_RECHARGE, .maxSpawnCount = 5, .spawnCount = 0},
            {.type = ENEMY_TYPE_RADIUS, .maxSpawnCount = 7, .spawnCount = 0}
        },
        .enemyTypeCount = 3,
        .enemyMinSpawnCount = 12,
        .enemyMaxSpawnCount = 15
    },
    
    // Stage 9 (min 15 max 20)
    {
        .spawnData = {
            {.type = ENEMY_TYPE_JUGGERNAUT, .maxSpawnCount = 3, .spawnCount = 0},
            {.type = ENEMY_TYPE_SABOT, .maxSpawnCount = 7, .spawnCount = 0},
            {.type = ENEMY_TYPE_SENTRY, .maxSpawnCount = 4, .spawnCount = 0},
            {.type = ENEMY_TYPE_RADIUS, .maxSpawnCount = 7, .spawnCount = 0}
        },
        .enemyTypeCount = 4,
        .enemyMinSpawnCount = 15,
        .enemyMaxSpawnCount = 20
    }
};