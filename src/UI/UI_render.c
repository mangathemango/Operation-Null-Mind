#include <UI.h>
#include <app.h>
#include <SDL.h>
#include <SDL_ttf.h>

// Create texture once, and store it for reuse
SDL_Texture* UI_CreateTextTexture(const char* text, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(app.resources.textFont, text, color);
    if (!surface) return NULL;
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(app.resources.renderer, surface);
    SDL_FreeSurface(surface);
    
    return texture;  // Caller is responsible for freeing
}

// Render from existing texture (very fast)
void UI_RenderTextureText(SDL_Texture* texture, Vec2 destPosition, float scale) {
    SDL_Rect rect = {0, 0, 0, 0};
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.x = destPosition.x;
    rect.y = destPosition.y;
    rect.w *= scale;
    rect.h *= scale;

    if (texture) {
        SDL_RenderCopy(app.resources.renderer, texture, NULL, &rect);
    }
}

/*
*   [Render] Renders text to the screen.
?   This function creates a surface and a texture just to render one text.
?   This is really inefficient, and will waste a lot of memory if called every frame.
?   It's best to use UI_CreateTextTexture() and UI_RenderTextureText() instead.
*/
void UI_InefficientlyRenderText(const char* text, SDL_Rect rect, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(app.resources.textFont, text, color);
    if (!surface) return;
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(app.resources.renderer, surface);
    SDL_FreeSurface(surface);
    
    if (texture) {
        SDL_RenderCopy(app.resources.renderer, texture, NULL, &rect);
        SDL_DestroyTexture(texture);
    }
}