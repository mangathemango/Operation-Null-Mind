#pragma once

#include <app.h>

typedef struct {
    int currentStage;
    bool isTransitioning;
    Timer* transitionTimer;

    int viewingLog;
} GameData;

extern GameData game;

void Game_Start();
void Game_Update();
void Game_TransitionNextLevel();
