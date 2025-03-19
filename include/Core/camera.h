/*
*   @file camera.h
?   This file contains the declarations for the camera system.
?   The camera system is used to convert between world and screen coordinates.

?   For most objects, the variable "position" is in world coordinates.
?   That's why, the Camera_WorldVecToScreen() function is used in render functions to convert that position to screen coordinates.

?   For example: in src/Game/Player/Base/player_render.c
?      Animation_Render(
?          player.resources.animation,            
*          Camera_WorldVecToScreen(
*              Vec2_Subtract (
*                  player.state.position,
*                  Vec2_Divide(player.animData.spriteSize, 2)
*              )
*          ), // This is the position to render the thing
?          player.animData.spriteSize,
?          0,
?          NULL,
?          flip
?      );
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