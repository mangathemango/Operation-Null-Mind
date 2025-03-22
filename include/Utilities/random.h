/**
 * @file random.h
 * @brief This file contains the random number generator functions.
 *
 * These functions can be used to generate random integers and floats.
 * To use these functions, call RandomInit() once at the start of the program.
 * Then, call RandInt() or RandFloat() to get random numbers.
 *
 * @author Mango
 * @date 2025-03-03
 */

#pragma once
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/**
 * @brief Initializes the random number generator.
 *
 * This function should be called once at the start of the program.
 */
void RandomInit();

/**
 * @brief Generates a random integer between min and max (inclusive).
 * @param min The minimum value.
 * @param max The maximum value.
 * @return A random integer between min and max.
 */
int RandInt(int min, int max);

/**
 * @brief Generates a random float between min and max.
 * @param min The minimum value.
 * @param max The maximum value.
 * @return A random float between min and max.
 */
float RandFloat(float min, float max);

/**
 * @brief Generates a random boolean value.
 * @return A random boolean value (true or false).
 */
bool RandBool();
