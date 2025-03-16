#include <debug.h>
#include <app.h>
#include <colliders.h>
#include <stdio.h>
#include <UI_text.h>
#include <camera.h>

#define PLAYER_HITBOX_COLOR 0, 255, 0, 255
#define WALL_HITBOX_COLOR 255, 255, 0, 255
#define ENEMY_HITBOX_COLOR 255, 0, 0, 255
#define ITEM_HITBOX_COLOR 0, 255, 255, 255
#define ENEMY_PROJECTILE_HITBOX_COLOR 255, 0, 255, 255
#define PLAYER_PROJECTILE_HITBOX_COLOR 0, 0, 255, 255

/*
*   [Render?] Renders every single hitbox in the game.
*/
void Debug_RenderHitboxes() {
    if (!app.config.debug) return;
    for (int i = 0; i < ColliderCount; i++) {
        Collider* collider = ColliderList[i];
        if (!collider->active) continue;
        SDL_Rect hitbox = collider->hitbox;
        hitbox.x = Camera_WorldToScreen((Vec2) {hitbox.x, hitbox.y}).x;
        hitbox.y = Camera_WorldToScreen((Vec2) {hitbox.x, hitbox.y}).y;
        if (hitbox.x > app.config.screen_width || hitbox.y > app.config.screen_height) continue;
        if (hitbox.x + hitbox.w < 0 || hitbox.y + hitbox.h < 0) continue;
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

/*
*   [Render] Renders the current FPS count on the screen.
*/
void Debug_RenderFPSCount() {
    if (!app.config.debug) return;
    // The UIElement struct stored in a static variable for reuse
    static UIElement* fpsTextElement = NULL;

    // Format FPS text
    char fpsText[16];
    sprintf(fpsText, "FPS: %d", app.state.fps);


    if (!fpsTextElement) {
        // Create text element if it doesn't exist 

        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Rect renderRect = {10, 10, 0, 0};   
        float textScale = 1;
        UI_TextAlignment alignment = UI_TEXT_ALIGN_LEFT;

        fpsTextElement = UI_CreateText(
            fpsText, 
            renderRect, 
            textColor, 
            textScale, 
            alignment, 
            app.resources.textFont
        );
    } else {
        // Update text if it does exist.
        UI_ChangeText(fpsTextElement, fpsText);
    }

    // Update and render text
    UI_UpdateText(fpsTextElement);
    UI_RenderText(fpsTextElement);
}