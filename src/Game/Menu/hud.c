#include <hud.h>
#include <app.h>

static SDL_Texture* healthTexture;
static SDL_Texture* ammoTexture;

void HUD_Start() {
    healthTexture = IMG_LoadTexture(app.resources.renderer, "Assets/Images/Icons/health.png");
    ammoTexture = IMG_LoadTexture(app.resources.renderer, "Assets/Images/Icons/ammo.png");
}

void HUD_Render() {
    Vec2 barSize = {120, 12};
    Vec2 iconSize = {10, 10};
    float barX = 20;
    float iconX = 22;
    Vec2 healthBarPosition = (Vec2) {barX, app.config.screen_height - 20};
    Vec2 ammoBarPosition = (Vec2) {barX, app.config.screen_height - 40};

    SDL_Rect barDest = Vec2_ToRect(healthBarPosition, barSize);
    SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(app.resources.renderer, &barDest);

    SDL_Rect iconDest = (SDL_Rect) {
        iconX, 
        healthBarPosition.y + (barSize.y - iconSize.y) / 2, 
        10,
        10
    };
    SDL_RenderCopy(app.resources.renderer, healthTexture, NULL, &iconDest);


    barDest = Vec2_ToRect(ammoBarPosition, barSize);
    SDL_RenderFillRect(app.resources.renderer, &barDest);
    iconDest = (SDL_Rect) {
        iconX, 
        ammoBarPosition.y + (barSize.y - iconSize.y) / 2, 
        10,
        10
    };
    SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
    SDL_RenderCopy(app.resources.renderer, ammoTexture, NULL, &iconDest);
}