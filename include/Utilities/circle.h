#pragma once

#include <SDL.h>
#include <vec2.h>

void DrawFilledCircle(Vec2 center, int radius, SDL_Color color);
bool IsRectOverlappingCircle(SDL_Rect rect, Vec2 circleCenter, float radius);