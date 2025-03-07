#include <timer.h>
#include <time_system.h>
#include <stdlib.h>

/*
*   [Start/Utility] Creates a timer
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

/*
*   [Utility] Starts the timer
*/
void Timer_Start(Timer *timer) {
    timer->startTime = Time->programElapsedTimeSeconds;
    timer->inProgress = true;
    timer->finished = false;
}

/*
*   [Utility] Determines whether a timer is finished
?   A timer is finished when  Current Time - Timer start time > Timer duration
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

float Timer_GetTimeLeft(Timer *timer) {
    if (!timer->inProgress) return 0;
    return timer->duration - timer->elapsedTime;
}

/*
*   [Utility] Determines whether a timer is in progress
*/
bool Timer_IsInProgress(Timer *timer) {
    return timer->inProgress;
}

/*
*   [Utility] Destroys a timer
*/
void Timer_Destroy(Timer *timer) {
    free(timer);
}