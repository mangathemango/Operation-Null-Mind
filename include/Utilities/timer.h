/**
 * @file timer.h
 * @brief This file contains the Timer struct and its functions.
 *
 * Timer has many different uses - for cooldowns, fire rates, animations, etc.
 * Right now, it's just a simple timer that can only be started, but not paused or stopped.
 *
 * The way you use the timer is by creating a Timer object, setting its duration, and starting it.
 * You can check if the timer is finished or in progress by using Timer_IsFinished() and Timer_IsInProgress().
 *
 * @deprecated The below example is deprecated and will be updated soon.
 * @example Cooldown System Example
 * @subsection usage_cooldown Usage in a cooldown system
 * ```c
 * void foo() {
 *     static Timer* cooldown = NULL;          // Make sure this is static
 *
 *     if (cooldown != NULL) {                 // Check there's a cooldown timer in progress
 *         if (Timer_IsFinished(cooldown)) {
 *             Timer_Destroy(cooldown);        // Destroy the cooldown timer if it's finished
 *                                             // This is important to prevent memory leaks    
 *             cooldown = NULL;
 *         } else {
 *             return;                         // Return if the cooldown is still in progress
 *         }
 *     }    
 *
 *     // Do something that requires a cooldown
 *
 *     cooldown = Timer_Create(1); // 1 second cooldown
 *     Timer_Start(cooldown); // Start the cooldown
 * }
 * ```
 *
 * @author Mango
 * @date 2025-03-02
 */

#pragma once
#include <SDL.h>
#include <stdbool.h>

/**
 * @brief The Timer struct used to keep track of time.
 *
 * Used for cooldowns, delays, etc. It has a start time, an elapsed time, 
 * a duration, and flags to check if the timer is in progress or finished.
 */
typedef struct {
    float startTime;    /**< Time when the timer was started */
    float elapsedTime;  /**< Time elapsed since the timer was started */
    float duration;     /**< Duration of the timer in seconds */
    bool inProgress;    /**< Flag indicating if the timer is in progress */
    bool finished;      /**< Flag indicating if the timer is finished */
} Timer;

/**
 * @brief Creates a new timer with the specified duration.
 * @param duration The duration of the timer in seconds.
 * @return A pointer to the newly created timer.
 */
Timer* Timer_Create(float duration);

/**
 * @brief Starts the timer.
 * @param timer The timer to start.
 */
void Timer_Start(Timer *timer);

/**
 * @brief Checks if the timer is finished.
 * @param timer The timer to check.
 * @return true if the timer is finished, false otherwise.
 */
bool Timer_IsFinished(Timer *timer);

/**
 * @brief Gets the time left on the timer.
 * @param timer The timer to check.
 * @return The time left in seconds.
 */
float Timer_GetTimeLeft(Timer *timer);

/**
 * @brief Checks if the timer is in progress.
 * @param timer The timer to check.
 * @return true if the timer is in progress, false otherwise.
 */
bool Timer_IsInProgress(Timer *timer);

/**
 * @brief Destroys the timer and frees its memory.
 * @param timer The timer to destroy.
 */
void Timer_Destroy(Timer *timer);