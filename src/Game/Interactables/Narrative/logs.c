#include <app.h>
#include <logs.h>

static SDL_Texture* logTexture;

void Log_Start() {
    logTexture = IMG_LoadTexture(app.resources.renderer, "Assets/Images/Logs/log_1.png");
}

void Log_Create(int logIndex, Vec2 position) {
    Interactable_Create(INTERACTABLE_LOG, position);
    interactables[logIndex].spriteTexture = logTexture;
    interactables[logIndex].hitboxSize = (Vec2) {8.5 * 25, 11 * 25};
    interactables[logIndex].renderSize = (Vec2) {8.5 * 25, 11 * 25};
}

void Log_Render() {
    float scale = 25;
    float width = 8.5 * scale;
    float height = 11 * scale;
    SDL_Rect dest = {
        app.config.screen_width/2 - width/2, 
        app.config.screen_height / 2 - height/2,
        width, 
        height
    };
    SDL_RenderCopy(app.resources.renderer, logTexture, NULL, &dest);
}