#pragma once

#include <app.h>

typedef struct {
    int currentStage;
    bool isTransitioning;
    Timer* transitionTimer;

    int viewingLog;
    bool hudToggled;
} GameData;

extern GameData game;

void Game_Start();
void Game_Update();
void Game_Restart();
void Game_TransitionNextLevel(void* data, int interactableIndex);
void Player_PickUpHealth(void* data, int interactableIndex);
void Player_PickUpSkill(void* data, int interactableIndex);
