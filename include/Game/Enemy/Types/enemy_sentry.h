/**
 * @file enemy_sentry.h
 * @brief This file contains the data for the Sentry enemy type.
 *
 * @author Mango
 * @date 2025-03-22
 */

#pragma once
#include <enemy.h>

typedef struct {
    float guardRadius;       // Radius that the sentry will guard
    float alertLevel;        // Current alert level (0.0-1.0)
    float alertThreshold;    // Threshold at which sentry becomes alerted
    bool isAlerted;          // Flag indicating if sentry is alerted
    Vec2 guardPosition;      // Central position the sentry is guarding
} SentryConfig;

void Sentry_Start (EnemyData* data);
void Sentry_Update(EnemyData* data);
void Sentry_Render(EnemyData* data);

extern SentryConfig SentryConfigData;
extern EnemyData SentryData;
