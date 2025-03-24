/**
 * @file time_system.h
 * @brief Manages time-related functionality for frame rate independence and timing.
 * 
 * The time system struct is used to keep track of the program's time, delta time, and time scale.
 * Time delta is the time between the current frame and the previous frame.
 * It's super useful for making sure that the game runs at the same speed on different fps.
 * 
 * @subsection usage Example Usage:
 * Usage in updating the position of an object that's moving up with the speed of 5 units per second.
 *
 * It is quite tempting to move an object something like this:
 * ```c
 * // This line is called every frame
 * object.y -= 5; // btw in SDL reducing y moves the object up
 * ```
 * Since this is called every frame, the speed will be 5 units/frame. Which causes the speed to be dependent on the frame rate.
 * 
 * To make the speed independent of the frame rate, we can use the delta time like this:
 * ```c
 * // This line is called every frame
 * object.y -= 5 * Time->deltaTimeSeconds; // Do this instead!
 * ```
 * This way, the object will move up 5 units per second regardless of the frame rate.
 * 
 * @author Mango
 * @date 2025-01-03
 */

#pragma once
#include <SDL.h>

/**
 * @brief Structure to handle time-related functionality
 */
typedef struct {
    float deltaTimeSeconds;      /**< Time between current frame and previous frame in seconds */
    float timeScale;             /**< Scale factor for time */
    float scaledDeltaTimeSeconds; /**< Delta time multiplied by time scale */
    double programElapsedTimeSeconds; /**< Total time elapsed since program start */
    double previousTick;         /**< Previous frame tick value */
} TimeSystem;

extern const TimeSystem * const Time;

void Time_PreUpdate();
void Time_UpdateFPS();
void Time_SetTimeScale(float scale);
void Time_ResetTotalTime();
