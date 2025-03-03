#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SDL.h>

typedef struct {
    SDL_FRect position;
    SDL_Rect hitbox;
} Rectangle;

void init_rectangle(Rectangle* rect, float x, float y, float w, float h);
void render_rectangle(Rectangle* rect, SDL_Renderer* renderer);

#endif