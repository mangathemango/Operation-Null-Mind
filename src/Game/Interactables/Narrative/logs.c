#include <app.h>
#include <interactable.h>
#include <logs.h>
#include <stdio.h>
#include <game.h>

#define LOG_COUNT 6
static SDL_Texture* logTexture[LOG_COUNT];

void Log_Start() {
    for (int i = 0; i < LOG_COUNT; i ++) {
        char path[50];
        sprintf(path, "Assets/Images/Logs/log_%d.png", i + 1);
        logTexture[i] = IMG_LoadTexture(app.resources.renderer, path);
        if (!logTexture[i]) {
            SDL_Log("Failed to load log texture %d: %s", i, IMG_GetError());
        }
    }
    
}

void Interactable_CreateLog(int logIndex, Vec2 position) {
    int index = Interactable_Create(INTERACTABLE_LOG, position);
    int* data = malloc(sizeof(int));
    *data = logIndex;
    interactables[index].data = data;
}

void Log_Render() {
    static float currentOffset = 0.0f;
    float targetOffset;
    if (game.viewingLog == -1) {
        targetOffset = 0;
    } else {
        targetOffset = app.config.screen_height;
    }
    float moveSpeed = 0.1f;
    currentOffset = currentOffset * (1 - moveSpeed) + targetOffset * moveSpeed;

    float scale = 25;
    float width = 8.5 * scale;
    float height = 11 * scale;
    SDL_Rect dest = {
        app.config.screen_width/2 - width/2, 
        -app.config.screen_height / 2 - height/2 + currentOffset,
        width, 
        height
    };
    static int index = -1;
    if (!Camera_ScreenRectIsOnScreen(dest)) {
        return;
    }
    if (game.viewingLog != -1) {
        index = game.viewingLog;
    }
    SDL_RenderCopy(app.resources.renderer, logTexture[index], NULL, &dest);
}