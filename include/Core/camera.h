/**
 * @file camera.h
 * @brief Provides camera functionality for world-to-screen coordinate conversion.
 * @image html camera.png width=400px
 * The camera system is used to convert between world and screen coordinates.
 * For most objects, the variable "position" is in world coordinates.
 * That's why, the Camera_WorldVecToScreen() function is used in render functions to convert that position to screen coordinates.
 * Vice versa, the Camera_ScreenVecToWorld() function is used to convert screen coordinates to world coordinates.
 * @author Mango
 * @date 2025-03-12
 * 
 * @section usage Usage Examples
 * 
 * ```c
 * player.state.position // This is world position
 * Vec2 screenPosition = Camera_WorldVecToScreen(player.state.position); // screenPosition is now the screen position of the player
 * 
 * // We can now render the player at the screen position
 * ```
 */

#pragma once

#include <vec2.h>
#include <SDL.h>
#include <stdbool.h>

typedef struct {
    Vec2 position;
} CameraSystem;

extern CameraSystem camera;

void Camera_UpdatePosition();

Vec2 Camera_WorldVecToScreen(Vec2 worldPosition);
Vec2 Camera_ScreenVecToWorld(Vec2 screenPosition);
SDL_Rect Camera_GetViewRect();
bool Camera_RectIsOnScreen(SDL_Rect rect);