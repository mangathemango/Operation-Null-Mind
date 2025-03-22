/**
 * @file random.c
 * @brief Random number generation utilities
 *
 * Provides functions for generating random integers, floats, and booleans
 * within specified ranges. Includes seed initialization.
 * 
 * @author Mango
 * @date 2025-03-05
 */

#include <random.h>

/**
 * [Start] Initializes the random number generator
 * 
 * Seeds the random number generator with a time-based value to ensure
 * different sequences on each program run.
 */
void RandomInit() {
    srand((unsigned int)time(NULL));
}

/**
 * [Utility] Generates a random integer within a range
 * 
 * Creates a random integer value that is >= min and <= max.
 * The distribution is uniform across the range.
 * 
 * @param min The minimum value (inclusive)
 * @param max The maximum value (inclusive)
 * @return int A random integer between min and max
 */
int RandInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

/**
 * [Utility] Generates a random float within a range
 * 
 * Creates a random floating-point value that is >= min and <= max.
 * The distribution is uniform across the range.
 * 
 * @param min The minimum value (inclusive)
 * @param max The maximum value (inclusive)
 * @return float A random float between min and max
 */
float RandFloat(float min, float max) {
    return (float)rand() / RAND_MAX * (max - min) + min;
}

/**
 * [Utility] Generates a random boolean value
 * 
 * Returns either true or false with equal probability (50%).
 * 
 * @return bool Either true or false
 */
bool RandBool() {
    return RandInt(0,1) == 0;
}