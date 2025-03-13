#pragma once

#include <vec2.h>
#include <SDL.h>


typedef struct {
    Vec2 position;
} CameraSystem;

extern CameraSystem camera;

Vec2 Camera_WorldToScreen(Vec2 worldPosition);
Vec2 Camera_ScreenToWorld(Vec2 screenPosition);