/**
 * @file timer.c
 * @brief Implementation of the timer utility
 *
 * Provides functionality for creating, starting, checking, and destroying timers.
 * Timers are used for cooldowns, fire rates, animations, and other time-based features.
 * 
 * @author Mango
 * @date 2025-03-02
 */

// Written by Mango on 02/03/2025

#include <timer.h>
#include <time_system.h>
#include <stdlib.h>

/**
 * @brief [Start/Utility] Creates a timer with the specified duration
 *
 * Allocates and initializes a new timer with the given duration.
 * The timer starts in a stopped state and must be started with Timer_Start().
 *
 * @param duration The duration of the timer in seconds
 * @return Timer* Pointer to the newly created timer
 */
Timer* Timer_Create(float duration) {
    Timer *timer = malloc(sizeof(Timer));
    timer->startTime = Time->programElapsedTimeSeconds;
    timer->elapsedTime = 0;
    timer->duration = duration;
    timer->inProgress = false;
    timer->finished = false;
    return timer;
}

/**
 * @brief [Utility] Starts or restarts a timer
 *
 * Sets the start time to the current time and marks the timer as in progress.
 * If the timer was already running, this will restart it.
 *
 * @param timer Pointer to the timer to start
 */
void Timer_Start(Timer *timer) {
    timer->startTime = Time->programElapsedTimeSeconds;
    timer->inProgress = true;
    timer->finished = false;
}

/**
 * @brief [Utility] Determines whether a timer is finished
 *
 * A timer is finished when Current Time - Timer start time > Timer duration.
 * If the timer is not running, returns the cached finished state.
 *
 * @param timer Pointer to the timer to check
 * @return bool True if the timer has finished, false otherwise
 */
bool Timer_IsFinished(Timer *timer) {
    if (timer->finished) return true;
    if (timer->inProgress) {
        timer->elapsedTime = Time->programElapsedTimeSeconds - timer->startTime;
        if (timer->elapsedTime >= timer->duration) {
            timer->finished = true;
            timer->inProgress = false;
            return true;
        }
    }
    return false;
}

/**
 * @brief [Utility] Gets the remaining time before a timer finishes
 *
 * Returns how many seconds are left before the timer completes.
 * Returns 0 if the timer is not running or has already finished.
 *
 * @param timer Pointer to the timer to check
 * @return float Time left in seconds, or 0 if the timer is not running
 */
float Timer_GetTimeLeft(Timer *timer) {
    if (!timer->inProgress) return 0;
    return timer->duration - timer->elapsedTime;
}

/**
 * @brief [Utility] Determines whether a timer is currently running
 *
 * Checks if the timer is in the "in progress" state.
 *
 * @param timer Pointer to the timer to check
 * @return bool True if the timer is in progress, false otherwise
 */
bool Timer_IsInProgress(Timer *timer) {
    return timer->inProgress;
}

/**
 * @brief [Utility] Destroys a timer and frees its memory
 *
 * @param timer Pointer to the timer to destroy
 */
void Timer_Destroy(Timer *timer) {
    free(timer);
}