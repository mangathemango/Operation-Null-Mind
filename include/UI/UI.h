#include <SDL.h>
#include <vec2.h>

SDL_Texture* UI_CreateTextTexture(const char* text, SDL_Color color);
void UI_RenderTextureText(SDL_Texture* texture, Vec2 destPosition, float scale);
void UI_InefficientlyRenderText(const char* text, SDL_Rect rect, SDL_Color color);