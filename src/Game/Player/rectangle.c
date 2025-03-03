#include "rectangle.h"
#include <SDL.h>

void init_rectangle(Rectangle* rect, float x, float y, float w, float h) {
    rect->position = (SDL_FRect){x, y, w, h};
    rect->hitbox = (SDL_Rect){(int)x, (int)y, (int)w, (int)h};
}

void render_rectangle(Rectangle* rect, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRectF(renderer, &rect->position);
}