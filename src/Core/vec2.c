#include <vec2.h>
#include <math.h>

/*
*   Returns the magnitude of a vector.

?   Magnitude is the length of a vector basically.
    @param v The vector to get the magnitude of.
*/
float Vec2_Magnitude(Vec2 v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

/*
*   Returns the normalized vector of a vector.

?   A normalized vector is a vector with a magnitude of 1, but faces the same direction as the input vector.
    @param v The vector to normalize.
*/
Vec2 Vec2_Normalize(Vec2 v) {
    float mag = Vec2_Magnitude(v);
    return (Vec2) {v.x / mag, v.y / mag};
}

/*
*   Add two vectors together, and returns the result.
    @param a The first vector to add.
    @param b The second vector to add.
*/
Vec2 Vec2_Add(Vec2 a, Vec2 b) {
    return (Vec2) {a.x + b.x, a.y + b.y};
}

/*
*   Subtract two vectors, and returns the result.
    @param a The vector to subtract from.
    @param b The vector to subtract.
    @returns The result of the subtraction a - b.
*/
Vec2 Vec2_Subtract(Vec2 a, Vec2 b) {
    return (Vec2) {a.x - b.x, a.y - b.y};
}

/*
*   Multiply a vector by a scalar, and returns the result.

    @param v The vector to multiply.
    @param scalar The scalar to multiply the vector by.
*/
Vec2 Vec2_Multiply(Vec2 v, float scalar) {
    return (Vec2) {v.x * scalar, v.y * scalar};
}

/*
*   Divide a vector by a scalar, and returns the result.

    @param v The vector to divide.
    @param scalar The scalar to divide the vector by.
    @returns The result of the division v / scalar.
*/
Vec2 Vec2_Divide(Vec2 v, float scalar) {
    return (Vec2) {v.x / scalar, v.y / scalar};
}

/*
*   Returns the dot product of two vectors.

    @param a The first vector.
    @param b The second vector.
    @returns The dot product of a and b.
*/
float Vec2_Dot(Vec2 a, Vec2 b) {
    return a.x * b.x + a.y * b.y;
}

/*
*   Returns the Linear Interpolation between two vectors.

    @param a The first vector.
    @param b The second vector.
    @param t The time to interpolate between the two vectors.
    @returns The linear interpolation between a and b at time t.
*/
Vec2 Vec2_Lerp(Vec2 a, Vec2 b, float t) {
    return (Vec2) {a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t};
}

Vec2 Vec2_Rotate(Vec2 v, float angle) {
    float x = v.x * cos(angle) - v.y * sin(angle);
    float y = v.x * sin(angle) + v.y * cos(angle);
    return (Vec2) {x, y};
}
