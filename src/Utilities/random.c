// Written by Mango on 05/03/2025

#include <random.h>

/*
*   [Start] Set random seed
*/
void RandomInit() {
    srand((unsigned int)time(NULL));
}

/*
*   [Utility] Get a random interger from a range
    @param min The minimum threshold
    @param min The maximum threshold
    @returns A random interger between min and max
*/
int RandInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

/*
*   [Utility] Get a random float from a range
    @param min The minimum threshold
    @param min The maximum threshold
    @returns A random float between min and max
*/
float RandFloat(float min, float max) {
    return (float)rand() / RAND_MAX * (max - min) + min;
}


/*
*   [Utility] Get a random boolean
    @returns Either true or false.
*/
bool RandBool() {
    return RandInt(0,1) == 0;
}