/**
 * @file enemy_juggernaut.h
 * @brief This file contains the data for the Juggernaut enemy type.
 *
 * @author Mango
 * @date 2025-03-22
 */

#pragma once
#include <enemy.h>

typedef struct {
    float armorValue;        // Damage reduction value
    float slowFactor;        // Movement speed reduction when activated
    float rageMeter;         // Current rage level (increases when damaged)
    bool isEnraged;          // Flag indicating if juggernaut is in enraged state
    float enrageThreshold;   // Threshold at which juggernaut becomes enraged
} JuggernautConfig;

void Juggernaut_Start (EnemyData* data);
void Juggernaut_Update(EnemyData* data);
void Juggernaut_Render(EnemyData* data);

extern JuggernautConfig JuggernautConfigData;
extern EnemyData JuggernautData;
