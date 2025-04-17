/**
 * @file time_system.c
 * @brief Game timing and frame rate management
 *
 * Handles game timing, delta time calculation, and frame rate
 * tracking to ensure consistent gameplay across different hardware.
 *
 * @author Mango
 * @date 2025-03-01
 */

//? Written by Mango on 01/03/2025

#include <time_system.h>
#include <app.h>

/**
 * @brief [Data] The initialization of the time system
 */
TimeSystem time = {
    .deltaTimeSeconds = 0,
    .timeScale = 1,
    .rawDeltaTimeSeconds = 0,
    .programElapsedTimeSeconds = 0,
    .rawProgramElapsedTimeSeconds = 0,
    .previousTick = 0
};

/** Global read-only time system pointer for other modules */
const TimeSystem * const Time = &time; // This ensures that the Time variable is read-only to other files.

/**
 * @brief [PreUpdate] Updates the time system values
 * 
 * Called at the beginning of each frame to calculate delta time and
 * other time-related metrics. Caps deltaTime to prevent spiral of death
 * if the game freezes temporarily.
 */
void Time_PreUpdate() {
    float currentTick = SDL_GetTicks();
    time.rawDeltaTimeSeconds = (currentTick - time.previousTick) / 1000;
    time.rawProgramElapsedTimeSeconds += time.rawDeltaTimeSeconds;
    time.deltaTimeSeconds = time.rawDeltaTimeSeconds * time.timeScale;
    if (time.deltaTimeSeconds > 0.1f) time.deltaTimeSeconds = 0.1f;
    time.programElapsedTimeSeconds += time.deltaTimeSeconds;
    time.previousTick = currentTick;
    Time_UpdateFPS();
}

/**
 * @brief [Utility] Updates the FPS counter
 * 
 * Calculates average FPS over different time scales to monitor
 * performance metrics for the game.
 */
void Time_UpdateFPS() {
    static int frameCount = 0;
    static int totalFrame = 0;
    static float fpsTimer = 0.0f;
    
    frameCount++;
    totalFrame++;
    fpsTimer += Time->rawDeltaTimeSeconds;
    
    // Update FPS once per second
    if (fpsTimer >= 0.5f) {
        app.state.fps = (int)(frameCount / fpsTimer);
        app.state.averageFps = (int)(totalFrame / time.programElapsedTimeSeconds);
        frameCount = 0;
        fpsTimer = 0.0f;
    }
}

/**
 * @brief [Utility] Sets the time scale.
 * 
 * Adjusts the game's time scale, which can speed up or slow down
 * the entire game. A value of 1.0 is normal speed, while 2.0 would
 * be double speed and 0.5 would be half speed.
 * 
 * @param scale The scale to set the time to.
 */
void Time_SetTimeScale(float scale) {
    time.timeScale = scale;
}

/**
 * @brief [Utility] Resets the total time elapsed in the program.
 * 
 * Zeroes out the accumulated program time, useful for timing specific
 * operations or resetting game timers.
 */
void Time_ResetTotalTime() {
    time.programElapsedTimeSeconds = 0;
}