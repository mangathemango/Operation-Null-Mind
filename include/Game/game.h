#pragma once

#include <app.h>

typedef struct {
    int currentStage;
    bool isTransitioning;
    Timer* transitionTimer;

    int viewingLog;
    bool hudToggled;
    float runTime;
    int ammoSpent;
    int hitsTaken;
    int healingItemsUsed;
} GameData;

extern GameData game;

void Game_Start();
void Game_Update();
void Game_Restart();
void Game_TransitionNextLevel(void* data, int interactableIndex);

// Game stat helper functions
void Game_AddAmmoSpent(int ammo);
void Game_AddHitsTaken();
void Game_AddHealingItemUsed();
