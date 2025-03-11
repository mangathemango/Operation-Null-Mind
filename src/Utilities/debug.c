#include <debug.h>
#include <app.h>
#include <colliders.h>
#include <stdio.h>
#include <UI.h>

#define PLAYER_HITBOX_COLOR 0, 255, 0, 255
#define WALL_HITBOX_COLOR 255, 255, 0, 255
#define ENEMY_HITBOX_COLOR 255, 0, 0, 255
#define ITEM_HITBOX_COLOR 0, 255, 255, 255
#define ENEMY_PROJECTILE_HITBOX_COLOR 255, 0, 255, 255
#define PLAYER_PROJECTILE_HITBOX_COLOR 255, 255, 0, 255

/*
*   [Render?] Renders the hitbox of the player and walls.
*/
void Debug_RenderHitboxes() {
    for (int i = 0; i < ColliderCount; i++) {
        Collider* collider = ColliderList[i];
        if (!collider->active) continue;
        SDL_Rect hitbox = collider->hitbox;
        switch (collider->layer) {
            case COLLISION_LAYER_PLAYER:
                SDL_SetRenderDrawColor(app.resources.renderer, PLAYER_HITBOX_COLOR);
                break;
            case COLLISION_LAYER_ENVIRONMENT:
                SDL_SetRenderDrawColor(app.resources.renderer, WALL_HITBOX_COLOR);
                break;
            case COLLISION_LAYER_ENEMY:
                SDL_SetRenderDrawColor(app.resources.renderer, ENEMY_HITBOX_COLOR);
                break;
            case COLLISION_LAYER_ITEM:
                SDL_SetRenderDrawColor(app.resources.renderer, ITEM_HITBOX_COLOR);
                break;
            case COLLISION_LAYER_ENEMY_PROJECTILE:
                SDL_SetRenderDrawColor(app.resources.renderer, ENEMY_PROJECTILE_HITBOX_COLOR);
                break;
            case COLLISION_LAYER_PLAYER_PROJECTILE:
                SDL_SetRenderDrawColor(app.resources.renderer, PLAYER_PROJECTILE_HITBOX_COLOR);
                break;
            default:
                SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
                break;
        }
        SDL_RenderDrawRect(app.resources.renderer, &hitbox);
    }
}

void Debug_RenderFPSCount() {
    static int lastRenderedFPS = -1;
    static SDL_Texture* fpsTexture = NULL;

    // Only recreate texture when FPS changes
    if (app.state.fps != lastRenderedFPS) {
        // Format FPS text
        char fpsText[16];
        sprintf(fpsText, "FPS: %d", app.state.fps);
        
        // Create text surface
        SDL_Color textColor = {255, 255, 255, 255};
        fpsTexture = UI_CreateTextTexture(fpsText, textColor);
        
        lastRenderedFPS = app.state.fps;
    }
    
    // Render the texture if it exists
    if (fpsTexture) {
        UI_RenderTextureText(fpsTexture, (Vec2){10, 10}, 0.5f);
    }
}