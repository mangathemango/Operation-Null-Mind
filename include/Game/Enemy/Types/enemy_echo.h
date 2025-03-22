/**
 * @file enemy_echo.h
 * @brief This file contains the data for the enemy **Echo**.
 *
 * @author Mango
 * @date 2025-03-19
 */

#pragma once
#include <enemy.h>

void Echo_Start (EnemyData* data);
void Echo_Update(EnemyData* data);
void Echo_Render(EnemyData* data);

extern EnemyData EchoData;