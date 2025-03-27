/**
 * @file enemy_kamikaze.h
 * @brief This file contains the data for the enemy **Echo**.
 *
 * @author Mango
 * @date 2025-03-19
 */

#pragma once
#include <enemy.h>

void Kamikaze_Start (EnemyData* data);
void Kamikaze_Update(EnemyData* data);
void Kamikaze_Render(EnemyData* data);

extern EnemyData KamikazeData;