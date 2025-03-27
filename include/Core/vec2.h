/**
 * @file vec2.h
 * @brief Provides 2D vector functionality for positions, directions, and transformations.
 * @details Being a top down 2D game, the Vec2 struct can be used to represent:
 *  
 *  - Positions
 *  
 *  - Velocities
 * 
 *  - Directions
 * 
 *  - Sizes
 * 
 *  - Offsets
 * 
 *  - And so on
 * 
 * The functions in this file can be used to perform common vector operations such as addition, subtraction, normalization, and rotation.
 * 
 * @section usage Usage Examples
 * 
 * @subsection usage1 Usage Examples1. Movement calculations:
 * ```c
 * Vec2 position = {10, 20};
 * Vec2 velocity = {5, 0};
 * 
 * // Move the position by the velocity
 * position = Vec2_Add(position, velocity);
 * ```
 * 
 * @subsection usage2 2. Move towards a target:
 * ```c
 * Vec2 position = {10, 20};
 * Vec2 target = {100, 50};
 * float speed = 5;
 * 
 * // Calculate the direction to the target (Read more about Vec2_Normalize)
 * Vec2 direction = Vec2_Normalize(Vec2_Subtract(target, position));
 * 
 * // Move towards the target
 * position = Vec2_Add(position, Vec2_Multiply(direction, speed));
 * ```
 * 
 * @subsection usage3 3. Rendering a rectangle:
 * ```c
 * Vec2 position = {100, 200};
 * Vec2 size = {50, 50};
 * SDL_Rect renderRect = Vec2_ToRect(position, size);
 * SDL_SetRenderDrawColor(app.resources.renderer, 255, 0, 0, 255);
 * SDL_RenderFillRect(app.resources.renderer, &renderRect);
 * ```
 * 
 * In this case, the position (100, 200) represent where the top-left corner of the rectangle will be rendered.
 * 
 * If you want to render the rectangle centered around the position, you can use Vec2_ToCenteredRect:
 * 
 * ```c
 * // ...
 * SDL_Rect = Vec2_ToCenteredRect(position, size);
 * // ...
 * ```
 * Here's a visualization of this:
 * @image html Vec2_ToRect.png width=400px
 * 
 * 
 * @author Mango
 * @date 2025-02-28
 */

#include <SDL.h>
#include <stdbool.h>

#ifndef VEC2_H
#define VEC2_H

/**
 * @struct Vec2
 * @brief A 2D vector structure
 */
typedef struct 
{
    float x; /**< The x-coordinate of the vector */
    float y; /**< The y-coordinate of the vector */
} Vec2;

/** @brief Zero vector (0,0) */
static const Vec2 Vec2_Zero = {0, 0};
/** @brief Unit vector pointing up (0,-1) */
static const Vec2 Vec2_Up = {0, -1};
/** @brief Unit vector pointing down (0,1) */
static const Vec2 Vec2_Down = {0, 1};
/** @brief Unit vector pointing left (-1,0) */
static const Vec2 Vec2_Left = {-1, 0};
/** @brief Unit vector pointing right (1,0) */
static const Vec2 Vec2_Right = {1, 0};

/**
 * @brief Calculate the magnitude (length) of a vector
 * @param v The input vector
 * @return The magnitude as a float
 */
float Vec2_Magnitude(Vec2 v);

/**
 * @brief Calculate the distance between two vectors
 * @param a First vector
 * @param b Second vector
 * @return The distance as a float
 */
float Vec2_Distance(Vec2 a, Vec2 b);

/**
 * @brief Normalize a vector (make it unit length)
 * @param v The vector to normalize
 * @return The normalized vector
 */
Vec2 Vec2_Normalize(Vec2 v);

/**
 * @brief Add two vectors
 * @param a First vector
 * @param b Second vector
 * @return The resulting vector
 */
Vec2 Vec2_Add(Vec2 a, Vec2 b);

/**
 * @brief Increment vector a by vector b
 * @param a Pointer to the first vector
 * @param b Second vector
 * @return The incremented vector
 */
Vec2 Vec2_Increment(Vec2* a, Vec2 b);

/**
 * @brief Subtract vector b from vector a
 * @param a First vector
 * @param b Second vector
 * @return The resulting vector
 */
Vec2 Vec2_Subtract(Vec2 a, Vec2 b);

/**
 * @brief Decrement vector a by vector b
 * @param a Pointer to the first vector
 * @param b Second vector
 * @return The decremented vector
 */
Vec2 Vec2_Decrement(Vec2* a, Vec2 b);

/**
 * @brief Multiply a vector by a scalar
 * @param v The vector
 * @param scalar The scalar value
 * @return The resulting vector
 */
Vec2 Vec2_Multiply(Vec2 v, float scalar);

/**
 * @brief Divide a vector by a scalar
 * @param v The vector
 * @param scalar The scalar value
 * @return The resulting vector
 */
Vec2 Vec2_Divide(Vec2 v, float scalar);

/**
 * @brief Calculate the dot product of two vectors
 * @param a First vector
 * @param b Second vector
 * @return The dot product as a float
 */
float Vec2_Dot(Vec2 a, Vec2 b);

/**
 * @brief Linearly interpolate between two vectors
 * @param a First vector
 * @param b Second vector
 * @param t Interpolation factor (0 to 1)
 * @return The interpolated vector
 */
Vec2 Vec2_Lerp(Vec2 a, Vec2 b, float t);

/**
 * @brief Rotate a vector by an angle in degrees
 * @param v The vector
 * @param angle The angle in degrees
 * @return The rotated vector
 */
Vec2 Vec2_RotateDegrees(Vec2 v, float angle);

/**
 * @brief Rotate a vector by an angle in radians
 * @param v The vector
 * @param angle The angle in radians
 * @return The rotated vector
 */
Vec2 Vec2_RotateRadians(Vec2 v, float angle);

/**
 * @brief Rotate a point around a center by an angle in radians
 * @param point The point to rotate
 * @param center The center of rotation
 * @param angle The angle in radians
 * @return The rotated point
 */
Vec2 Vec2_RotateAroundRadians(Vec2 point, Vec2 center, float angle);

/**
 * @brief Rotate a point around a center by an angle in degrees
 * @param point The point to rotate
 * @param center The center of rotation
 * @param angle The angle in degrees
 * @return The rotated point
 */
Vec2 Vec2_RotateAroundDegrees(Vec2 point, Vec2 center, float angle);

/**
 * @brief Convert a position and size to an SDL_Rect
 * @param position The position vector
 * @param size The size vector
 * @return The resulting SDL_Rect
 */
SDL_Rect Vec2_ToRect(Vec2 position, Vec2 size);

/**
 * @brief Convert a position and size to a centered SDL_Rect
 * @param position The position vector
 * @param size The size vector
 * @return The resulting centered SDL_Rect
 */
SDL_Rect Vec2_ToCenteredRect(Vec2 position, Vec2 size);

/**
 * @brief Convert a position and size to a centered position
 * @param position The position vector
 * @param size The size vector
 * @return The resulting centered position vector
 */
Vec2 Vec2_ToCenteredPosition(Vec2 position, Vec2 size);

/**
 * @brief Extract position and size from an SDL_Rect
 * @param rect The SDL_Rect
 * @param position Pointer to the position vector
 * @param size Pointer to the size vector
 */
void Vec2_FromRect(SDL_Rect rect, Vec2* position, Vec2* size);

/**
 * @brief Clamp a vector between two vectors
 * @param v The vector to clamp
 * @param min The minimum vector
 * @param max The maximum vector
 * @return The clamped vector
 */
Vec2 Vec2_Clamp(Vec2 v, Vec2 min, Vec2 max);

/**
 * @brief Get the maximum of two vectors
 * @param a First vector
 * @param b Second vector
 * @return The maximum vector
 */
Vec2 Vec2_Max(Vec2 a, Vec2 b);

/**
 * @brief Get the minimum of two vectors
 * @param a First vector
 * @param b Second vector
 * @return The minimum vector
 */
Vec2 Vec2_Min(Vec2 a, Vec2 b);

/**
 * @brief Get the absolute value of a vector
 * @param v The vector
 * @return The absolute value vector
 */
Vec2 Vec2_Abs(Vec2 v);

/**
 * @brief Convert an SDL_Point to a Vec2
 * @param point The SDL_Point
 * @return The resulting Vec2
 */
Vec2 Vec2_FromPoint(SDL_Point point);

/**
 * @brief Convert a Vec2 to an SDL_Point
 * @param v The vector
 * @return The resulting SDL_Point
 */
SDL_Point Vec2_ToPoint(Vec2 v);

bool Vec2_AreEqual(Vec2 a, Vec2 b);
Vec2 Vec2_Square(float side);
SDL_Rect Vec2_ToSquareRect(Vec2 position, float side);
SDL_Rect Vec2_ToCenteredSquareRect(Vec2 position, float side);
#endif