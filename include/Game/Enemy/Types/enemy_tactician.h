/**
 * @file enemy_tactician.h
 * @brief This file contains the data for the Tactician enemy type.
 *
 * @author Mango
 * @date 2025-03-22
 */

#pragma once
#include <enemy.h>

typedef struct {
    float commandRadius;     // Radius within which the tactician can control other enemies
    float buffStrength;      // Strength of buffs provided to other enemies
    int maxControlledUnits;  // Maximum number of units that can be controlled
    bool isCommanding;       // Flag indicating if tactician is commanding other units
    int controlledUnitCount; // Current number of units being controlled
} TacticianConfig;

void Tactician_Start (EnemyData* data);
void Tactician_Update(EnemyData* data);
void Tactician_Render(EnemyData* data);

extern TacticianConfig TacticianConfigData;
extern EnemyData TacticianData;
