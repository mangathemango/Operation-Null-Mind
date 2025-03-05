#include <timer.h>
#include <time_system.h>
#include <stdlib.h>

Timer* Timer_Create(float duration) {
    Timer *timer = malloc(sizeof(Timer));
    timer->startTime = Time->programElapsedTimeSeconds;
    timer->elapsedTime = 0;
    timer->duration = duration;
    timer->inProgress = false;
    timer->finished = false;
    return timer;
}

void Timer_Start(Timer *timer) {
    timer->startTime = Time->programElapsedTimeSeconds;
    timer->inProgress = true;
    timer->finished = false;
}

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

bool Timer_IsInProgress(Timer *timer) {
    return timer->inProgress;
}

void Timer_Destroy(Timer *timer) {
    free(timer);
}