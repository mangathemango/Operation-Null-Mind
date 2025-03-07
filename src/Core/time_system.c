#include <time_system.h>

TimeSystem time = {
    .deltaTimeSeconds = 0,
    .timeScale = 1,
    .scaledDeltaTimeSeconds = 0,
    .programElapsedTimeSeconds = 0,
    .previousTick = 0
};

const TimeSystem * const Time = &time; // This ensures that the Time variable is read-only to other files.

/*
*   This function is called inside App_PreUpdate().
?   It updates the time system. Like the delta time, the scaled delta time, the program elapsed time etc.
*/
void Time_PreUpdate() {
    float currentTick = SDL_GetTicks();
    time.deltaTimeSeconds = (currentTick - time.previousTick) / 1000;
    time.previousTick = currentTick;
    time.scaledDeltaTimeSeconds = time.deltaTimeSeconds * time.timeScale;
    time.programElapsedTimeSeconds += time.deltaTimeSeconds;
}

/*
*   Sets the time scale.

?   Time scale is a value that can be used to speed up or slow down the game.
?   A time scale of 1 is normal speed, 2 is twice as fast, 0.5 is half as fast etc.
    @param scale The scale to set the time to.
*/
void Time_SetTimeScale(float scale) {
    time.timeScale = scale;
}

/*
*   Resets the total time elapsed in the program.
*/
void Time_ResetTotalTime() {
    time.programElapsedTimeSeconds = 0;
}