/**
 * @file camera.h
 * @brief This file contains the declarations for the camera system.
 * @image html camera.png width=400px
 * The camera system is used to convert between world and screen coordinates.
 * For most objects, the variable "position" is in world coordinates.
 * That's why, the Camera_WorldVecToScreen() function is used in render functions to convert that position to screen coordinates.
 * @author Mango
 * @date 2025-03-12
 * 
 * @section usage Usage Examples
 * 
 * ```c
 * player.state.position
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