/*
    @file time_system.h
*   This file contains the time system struct and its functions.
?   The time system struct is used to keep track of the program's time, delta time, and time scale.
?   Time delta is the time between the current frame and the previous frame.
?   It's super useful for making sure that the game runs at the same speed on different fps.

?   Written by Mango on 01/03/2025
*/

#pragma once
#include <SDL.h>

typedef struct {
    float deltaTimeSeconds;
    float timeScale;
    float scaledDeltaTimeSeconds;
    double programElapsedTimeSeconds;
    double previousTick;
} TimeSystem;

extern const TimeSystem * const Time;

void Time_PreUpdate();
void Time_SetTimeScale(float scale);
void Time_ResetTotalTime();
