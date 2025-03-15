/*
    @file random.h
*   This file contains the random number generator functions.
?   These functions can be used to generate random integers and floats.
?   To use these functions, call RandomInit() once at the start of the program.
?   Then, call RandInt() or RandFloat() to get random numbers.

?   Written by Mango on 03/03/2025
*/

#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void RandomInit();
int RandInt(int min, int max);
float RandFloat(float min, float max);
bool RandBool();
