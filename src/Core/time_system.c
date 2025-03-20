//? Written by Mango on 01/03/2025

#include <time_system.h>
#include <app.h>

/*
*   [Data] the initialization of the time system
*/
TimeSystem time = {
    .deltaTimeSeconds = 0,
    .timeScale = 1,
    .scaledDeltaTimeSeconds = 0,
    .programElapsedTimeSeconds = 0,
    .previousTick = 0
};

const TimeSystem * const Time = &time; // This ensures that the Time variable is read-only to other files.

/*
*   [PreUpdate] This function is called inside App_PreUpdate().
?   It updates the time system. Like the delta time, the scaled delta time, the program elapsed time etc.
*/
void Time_PreUpdate() {
    float currentTick = SDL_GetTicks();
    time.deltaTimeSeconds = (currentTick - time.previousTick) / 1000;
    if (time.deltaTimeSeconds > 0.1f) time.deltaTimeSeconds = 0.1f;
    time.previousTick = currentTick;
    time.scaledDeltaTimeSeconds = time.deltaTimeSeconds * time.timeScale;
    time.programElapsedTimeSeconds += time.deltaTimeSeconds;
    Time_UpdateFPS();
}

void Time_UpdateFPS() {
    static int frameCount = 0;
    static int totalFrame = 0;
    static float fpsTimer = 0.0f;
    
    frameCount++;
    totalFrame++;
    fpsTimer += Time->deltaTimeSeconds;
    
    // Update FPS once per second
    if (fpsTimer >= 0.5f) {
        app.state.fps = (int)(frameCount / fpsTimer);
        app.state.averageFps = (int)(totalFrame / time.programElapsedTimeSeconds);
        frameCount = 0;
        fpsTimer = 0.0f;
    }
}

/*
*   [Utility] Sets the time scale.

?   Time scale is a value that can be used to speed up or slow down the game.
?   A time scale of 1 is normal speed, 2 is twice as fast, 0.5 is half as fast etc.
    @param scale The scale to set the time to.
*/
void Time_SetTimeScale(float scale) {
    time.timeScale = scale;
}

/*
*   [Utility] Resets the total time elapsed in the program.
*/
void Time_ResetTotalTime() {
    time.programElapsedTimeSeconds = 0;
}