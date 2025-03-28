#pragma once

#include <SDL.h>
#include <vec2.h>

void DrawFilledCircle(Vec2 center, int radius, SDL_Color color);
bool IsRectOverlappingCircle(SDL_Rect rect, Vec2 circleCenter, float radius);
SDL_Texture* CreateCircleTexture(int radius, SDL_Color color);
void DrawCircleOutline(Vec2 center, int radius, SDL_Color color);
SDL_Texture* CreateCircleOutlineTexture(int radius, SDL_Color color, int thickness);