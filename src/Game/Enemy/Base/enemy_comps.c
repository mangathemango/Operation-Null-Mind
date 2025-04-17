#include <enemy.h> 
#include <stdlib.h>
#include <time.h>
#include <random.h>

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
    },

    // Stage 10 (Spawn only Libet)
    {
        .spawnData = {
            {.type = ENEMY_TYPE_LIBET, .maxSpawnCount = 1, .spawnCount = 0}
        },
        .enemyTypeCount = 1,
        .enemyMinSpawnCount = 1,
        .enemyMaxSpawnCount = 1
    },
};

/**
 * @brief Selects a random enemy type from the given enemy composition
 *
 * This function randomly selects an enemy type from the provided enemy composition,
 * taking into account the maximum spawn count for each enemy type. It returns a pointer
 * to the enemy data for the selected enemy type.
 *
 * @param comp Pointer to the enemy composition
 * @return Pointer to enemy data for the selected enemy type, or NULL if no valid enemy type can be selected
 */
EnemyData* Enemy_SelectRandomEnemyInComp(EnemyComp* comp) {
    // Count how many enemy types are available (haven't exceeded max spawn count)
    int availableTypes = 0;
    int availableIndices[ENEMY_TYPE_COUNT] = {0};
    
    // Find all available enemy types
    for (int i = 0; i < comp->enemyTypeCount; i++) {
        if (comp->spawnData[i].spawnCount == 0) {
            comp->spawnData[i].spawnCount = 1; // Ensure at least one spawn count for the first enemy type
            return enemyList[comp->spawnData[i].type];
        }

        if (comp->spawnData[i].spawnCount < comp->spawnData[i].maxSpawnCount) {
            availableIndices[availableTypes] = i;
            availableTypes++;
        }
    }
    
    // If no types are available, return NULL
    if (availableTypes == 0) {
        return NULL;
    }

    // Randomly select one of the available types
    int randomIndex = RandInt(0, availableTypes - 1);
    int selectedTypeIndex = availableIndices[randomIndex];
    
    // Increment spawn count for the selected enemy type
    comp->spawnData[selectedTypeIndex].spawnCount++;
    
    // Return the enemy data for the selected type
    return enemyList[comp->spawnData[selectedTypeIndex].type];
}

/**
 * @brief Resets the spawn counts in an enemy composition
 * 
 * This function resets all spawn counters in the provided enemy composition
 * to zero, allowing the composition to be reused for a new wave or stage.
 * 
 * @param comp Pointer to the enemy composition to reset
 */
void Enemy_ResetComp(EnemyComp* comp) {
    if (comp == NULL) {
        return;
    }
    
    // Reset spawn counts for all enemy types in the composition
    for (int i = 0; i < comp->enemyTypeCount; i++) {
        comp->spawnData[i].spawnCount = 0;
    }
}

