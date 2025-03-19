/*
    @file vec2.h
*   This file contains the Vec2 struct and its functions.
?   The Vec2 struct is a 2D vector that can be used for positions, directions, velocities etc.

?   Written by Mango on 28/02/2025
*/

#include <SDL.h>

#ifndef VEC2_H
#define VEC2_H
typedef struct 
{
    float x;
    float y;
} Vec2;

static const Vec2 Vec2_Zero = {0, 0};
static const Vec2 Vec2_Up = {0, -1};
static const Vec2 Vec2_Down = {0, 1};
static const Vec2 Vec2_Left = {-1, 0};
static const Vec2 Vec2_Right = {1, 0};

float Vec2_Magnitude(Vec2 v);
Vec2 Vec2_Normalize(Vec2 v);
Vec2 Vec2_Add(Vec2 a, Vec2 b);
Vec2 Vec2_Increment(Vec2* a, Vec2 b);
Vec2 Vec2_Subtract(Vec2 a, Vec2 b);
Vec2 Vec2_Decrement(Vec2* a, Vec2 b);
Vec2 Vec2_Multiply(Vec2 v, float scalar);
Vec2 Vec2_Divide(Vec2 v, float scalar);
float Vec2_Dot(Vec2 a, Vec2 b);
Vec2 Vec2_Lerp(Vec2 a, Vec2 b, float t);
Vec2 Vec2_RotateDegrees(Vec2 v, float angle);
Vec2 Vec2_RotateRadians(Vec2 v, float angle);
Vec2 Vec2_RotateAroundRadians(Vec2 point, Vec2 center, float angle);
Vec2 Vec2_RotateAroundDegrees(Vec2 point, Vec2 center, float angle);
SDL_Rect Vec2_ToRect(Vec2 position, Vec2 size);
SDL_Rect Vec2_ToCenteredRect(Vec2 position, Vec2 size);
Vec2 Vec2_ToCenteredPosition(Vec2 position, Vec2 size);
void Vec2_FromRect(SDL_Rect rect, Vec2* position, Vec2* size);
Vec2 Vec2_Clamp(Vec2 v, Vec2 min, Vec2 max);
Vec2 Vec2_Max(Vec2 a, Vec2 b);
Vec2 Vec2_Min(Vec2 a, Vec2 b);
Vec2 Vec2_Abs(Vec2 v);
Vec2 Vec2_FromPoint(SDL_Point point);
SDL_Point Vec2_ToPoint(Vec2 v);
#endif