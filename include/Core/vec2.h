/*
    @file vec2.h
*   This file contains the Vec2 struct and its functions.
?   The Vec2 struct is a 2D vector that can be used for positions, directions, velocities etc.
*/

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
Vec2 Vec2_Subtract(Vec2 a, Vec2 b);
Vec2 Vec2_Multiply(Vec2 v, float scalar);
Vec2 Vec2_Divide(Vec2 v, float scalar);
float Vec2_Dot(Vec2 a, Vec2 b);
Vec2 Vec2_Lerp(Vec2 a, Vec2 b, float t);
Vec2 Vec2_RotateDegrees(Vec2 v, float angle);
Vec2 Vec2_RotateRadians(Vec2 v, float angle);
Vec2 Vec2_RotateAround(Vec2 point, Vec2 center, float angle);
#endif