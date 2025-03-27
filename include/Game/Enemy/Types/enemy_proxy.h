/**
 * @file enemy_proxy.h
 * @brief This file contains the data for the Proxy enemy type.
 *
 * @author Mango
 * @date 2025-03-20
 */

#pragma once
#include <enemy.h>

typedef struct {
    float deployTime;        // Time required to deploy a proxy
    float proximityRadius;   // Activation radius for proxy behavior
    float damageMultiplier;  // Damage multiplier when proxy is active
    bool isDeployed;         // Flag indicating if proxy is currently deployed
    Vec2 deployPosition;     // Position where the proxy is deployed
} ProxyConfig;

void Proxy_Start (EnemyData* data);
void Proxy_Update(EnemyData* data);
void Proxy_Render(EnemyData* data);

extern ProxyConfig ProxyConfigData;
extern EnemyData ProxyData;
