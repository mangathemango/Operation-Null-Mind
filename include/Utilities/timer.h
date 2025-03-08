/*
    @file timer.h
*   This file contains the Timer struct and its functions.
?   Timer has many different uses - for cooldowns, fire rates, animations, etc.
?   Right now, it's just a simple timer that can only be started, but not paused or stopped.
?
?   The way you use the timer is by creating a Timer object, setting its duration, and starting it.
?   You can check if the timer is finished or in progress by using Timer_IsFinished() and Timer_IsInProgress().
?
!   The below example is deprecated and will be updated soon.
?   @example of how to use this in a cooldown system:
?
?   void foo() {
?       static Timer* cooldown = NULL;          // Make sure this is static
?
?       if (cooldown != NULL) {                 // Check there's a cooldown timer in progress
?           if (Timer_IsFinished(cooldown)) {
!               Timer_Destroy(cooldown);        // Destroy the cooldown timer if it's finished
!                                               // This is important to prevent memory leaks    
?               cooldown = NULL;
?           } else {
?               return;                         // Return if the cooldown is still in progress
?           }
?       }    
?
?       // Do something that requires a cooldown
?
?       Timer* cooldown = Timer_Create(1); // 1 second cooldown
?       Timer_Start(cooldown); // Start the cooldown
?   }

?   Written by Mango on 02/03/2025
*/

#pragma once
#include <SDL.h>
#include <stdbool.h>

/*
*   The Timer struct.
?   The Timer struct is used to keep track of time, used for cooldowns, delays, etc.
?   It has a start time, an elapsed time, a duration, and flags to check if the timer is in progress or finished.
*/
typedef struct {
    float startTime;
    float elapsedTime;
    float duration;
    bool inProgress;
    bool finished;
} Timer;

Timer* Timer_Create(float duration);
void Timer_Start(Timer *timer);
bool Timer_IsFinished(Timer *timer);
float Timer_GetTimeLeft(Timer *timer);
bool Timer_IsInProgress(Timer *timer);
void Timer_Destroy(Timer *timer);