// Written by Mango on 28/02/2025

#include <vec2.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

/*
*   [Utility] Returns the magnitude of a vector.
*   Magnitude is the length of a vector.
*   @param v The vector to get the magnitude of.
*   @returns The magnitude (length) of vector v.
*/
float Vec2_Magnitude(Vec2 v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

/*
*   [Utility] Returns the normalized vector of the input vector.
*   A normalized vector has a magnitude of 1 and the same direction as v.
*   @param v The vector to normalize.
*   @returns The normalized vector of v.
*/
Vec2 Vec2_Normalize(Vec2 v) {
    float mag = Vec2_Magnitude(v);
    return (Vec2) {v.x / mag, v.y / mag};
}

/*
*   [Utility] Adds two vectors.
*   @param a The first vector.
*   @param b The second vector.
*   @returns The resulting vector from a + b.
*/
Vec2 Vec2_Add(Vec2 a, Vec2 b) {
    return (Vec2) {a.x + b.x, a.y + b.y};
}

/*
*   [Utility] Increments the vector pointed to by a with vector b.
*   @param a Pointer to the vector to increment.
*   @param b The vector to add.
*   @returns The updated vector a (a + b).
*/
Vec2 Vec2_Increment(Vec2* a, Vec2 b) {
    a->x += b.x;
    a->y += b.y;
    return *a;
}

/*
*   [Utility] Subtracts vector b from vector a.
*   @param a The vector to subtract from.
*   @param b The vector to subtract.
*   @returns The result of a - b.
*/
Vec2 Vec2_Subtract(Vec2 a, Vec2 b) {
    return (Vec2) {a.x - b.x, a.y - b.y};
}

/*
*   [Utility] Decrements the vector pointed to by a by vector b.
*   @param a Pointer to the vector to decrement.
*   @param b The vector by which a will be decremented.
*   @returns The updated vector a after subtraction.
*/
Vec2 Vec2_Decrement(Vec2* a, Vec2 b) {
    a->x -= b.x;
    a->y -= b.y;
    return *a;
}

/*
*   [Utility] Multiplies a vector by a scalar.
*   @param v The vector to multiply.
*   @param scalar The scalar multiplier.
*   @returns The resulting vector v * scalar.
*/
Vec2 Vec2_Multiply(Vec2 v, float scalar) {
    return (Vec2) {v.x * scalar, v.y * scalar};
}

/*
*   [Utility] Divides a vector by a scalar.
*   @param v The vector to divide.
*   @param scalar The scalar divisor.
*   @returns The resulting vector v / scalar.
*/
Vec2 Vec2_Divide(Vec2 v, float scalar) {
    return (Vec2) {v.x / scalar, v.y / scalar};
}

/*
*   [Utility] Returns the dot product of two vectors.
*   @param a The first vector.
*   @param b The second vector.
*   @returns The dot product (a.x * b.x + a.y * b.y).
*/
float Vec2_Dot(Vec2 a, Vec2 b) {
    return a.x * b.x + a.y * b.y;
}

/*
*   [Utility] Linearly interpolates between vectors a and b.
*   @param a The start vector.
*   @param b The destination vector.
*   @param t The interpolation factor (0.0 to 1.0).
*   @returns The interpolated vector between a and b.
*/
Vec2 Vec2_Lerp(Vec2 a, Vec2 b, float t) {
    return (Vec2) {a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t};
}

/*
*   [Utility] Rotates a vector around the origin by a given angle (in radians).
*   @param v The vector to rotate.
*   @param angle The angle to rotate by in radians.
*   @returns The rotated vector.
*/
Vec2 Vec2_RotateRadians(Vec2 v, float angle) {
    float x = v.x * cos(angle) - v.y * sin(angle);
    float y = v.x * sin(angle) + v.y * cos(angle);
    return (Vec2) {x, y};
}

/*
*   [Utility] Rotates a vector around the origin by a given angle (in degrees).
*   @param v The vector to rotate.
*   @param angle The angle in degrees.
*   @returns The rotated vector.
*/
Vec2 Vec2_RotateDegrees(Vec2 v, float angle) {
    float angleRadians = angle * (M_PI / 180.0f);
    return Vec2_RotateRadians(v, angleRadians);
}

/*
*   [Utility] Rotates a point around a center by a given angle (in radians).
*   Translates the point to origin-relative, rotates it, then translates back.
*   @param point The point to rotate.
*   @param center The pivot for rotation.
*   @param angle The rotation angle in radians.
*   @returns The rotated point.
*/
Vec2 Vec2_RotateAroundRadians(Vec2 point, Vec2 center, float angle) {
    Vec2 translated = Vec2_Subtract(point, center);
    Vec2 rotated = Vec2_RotateRadians(translated, angle);
    return Vec2_Add(rotated, center);
}

/*
*   [Utility] Rotates a point around a center by a given angle (in degrees).
*   @param point The point to rotate.
*   @param center The pivot for rotation.
*   @param angle The rotation angle in degrees.
*   @returns The rotated point.
*/
Vec2 Vec2_RotateAroundDegrees(Vec2 point, Vec2 center, float angle) {
    float angleRadians = angle * (M_PI / 180.0f);
    return Vec2_RotateAroundRadians(point, center, angleRadians);
}

/*
*   [Utility] Converts a position and size into an SDL_Rect.
*   @param position The top-left position.
*   @param size The width and height.
*   @returns The SDL_Rect corresponding to position and size.
*/
SDL_Rect Vec2_ToRect(Vec2 position, Vec2 size) {
    return (SDL_Rect) {
        position.x,
        position.y,
        size.x,
        size.y
    };
}

/*
*   [Utility] Converts a position and size into a centered SDL_Rect.
*   Centers the rect at the specified position.
*   @param position The center position.
*   @param size The width and height.
*   @returns A centered SDL_Rect.
*/
SDL_Rect Vec2_ToCenteredRect(Vec2 position, Vec2 size) {
    return (SDL_Rect) {
        position.x - size.x / 2,
        position.y - size.y / 2,
        size.x,
        size.y
    };
}

/*
*   [Utility] Converts a position and size to a centered position.
*   Useful for positioning sprites centered on a coordinate.
*   @param position The top-left position.
*   @param size The size of the object.
*   @returns The centered position.
*/
Vec2 Vec2_ToCenteredPosition(Vec2 position, Vec2 size) {
    return (Vec2) {
        position.x - size.x / 2,
        position.y - size.y / 2
    };
}

/*
*   [Utility] Extracts a position and size from an SDL_Rect.
*   @param rect The SDL_Rect to decompose.
*   @param position Pointer to store the position.
*   @param size Pointer to store the size.
*/
void Vec2_FromRect(SDL_Rect rect, Vec2* position, Vec2* size) {
    position->x = rect.x;
    position->y = rect.y;
    size->x = rect.w;
    size->y = rect.h;
}

/*
*   [Utility] Clamps a vector between min and max vectors.
*   Ensures the vector's components stay within the provided bounds.
*   @param v The vector to clamp.
*   @param min The minimum values.
*   @param max The maximum values.
*   @returns The clamped vector.
*/
Vec2 Vec2_Clamp(Vec2 v, Vec2 min, Vec2 max) {
    return (Vec2) {
        fmin(fmax(v.x, min.x), max.x),
        fmin(fmax(v.y, min.y), max.y)
    };
}

/*
*   [Utility] Returns a vector that is the component-wise maximum of a and b.
*   @param a The first vector.
*   @param b The second vector.
*   @returns A vector of max components.
*/
Vec2 Vec2_Max(Vec2 a, Vec2 b) {
    return (Vec2) {
        fmax(a.x, b.x),
        fmax(a.y, b.y)
    };
}

/*
*   [Utility] Returns a vector that is the component-wise minimum of a and b.
*   @param a The first vector.
*   @param b The second vector.
*   @returns A vector of min components.
*/
Vec2 Vec2_Min(Vec2 a, Vec2 b) {
    return (Vec2) {
        fmin(a.x, b.x),
        fmin(a.y, b.y)
    };
}

/*
*   [Utility] Returns the absolute values of a vector's components.
*   @param v The vector to compute absolute values for.
*   @returns A vector where each component is the absolute value of v.
*/
Vec2 Vec2_Abs(Vec2 v) {
    return (Vec2) {
        fabs(v.x),
        fabs(v.y)
    };
}

/*
*   [Utility] Converts an SDL_Point to a Vec2.
*   @param point The SDL_Point to convert.
*   @returns The corresponding Vec2.
*/
Vec2 Vec2_FromPoint(SDL_Point point) {
    return (Vec2) {
        point.x,
        point.y
    };
}

/*
*   [Utility] Converts a Vec2 to an SDL_Point.
*   @param v The Vec2 to convert.
*   @returns The corresponding SDL_Point.
*/
SDL_Point Vec2_ToPoint(Vec2 v) {
    return (SDL_Point) {
        v.x,
        v.y
    };
}