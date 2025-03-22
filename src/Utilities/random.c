/**
 * @file random.c
 * @brief Random number generation utilities
 *
 * Provides functions for generating random integers, floats, and booleans
 * within specified ranges. Includes seed initialization.
 * 
 * Written by Mango on 05/03/2025
 */

#include <random.h>

/**
 * @brief Set random seed
 * 
 * Initializes the random number generator with a time-based seed.
 */
void RandomInit() {
    srand((unsigned int)time(NULL));
}

/**
 * @brief Get a random integer from a range
 * 
 * @param min The minimum threshold
 * @param max The maximum threshold
 * @return A random integer between min and max
 */
int RandInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

/**
 * @brief Get a random float from a range
 * 
 * @param min The minimum threshold
 * @param max The maximum threshold
 * @return A random float between min and max
 */
float RandFloat(float min, float max) {
    return (float)rand() / RAND_MAX * (max - min) + min;
}

/**
 * @brief Get a random boolean
 * 
 * @return Either true or false
 */
bool RandBool() {
    return RandInt(0,1) == 0;
}