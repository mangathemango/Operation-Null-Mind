/**
 * @file debug.c
 * @brief Debug visualization and information tools
 *
 * Provides functionality for rendering debug information like hitboxes,
 * FPS counters, and other metrics when debug mode is enabled.
 *
 * @author Mango
 * @date 2025-03-01
 */

#include <debug.h>
#include <app.h>
#include <colliders.h>
#include <interactable.h>
#include <stdio.h>
#include <UI_text.h>
#include <camera.h>
#include <maps.h>
#include <player.h>

/** Color constants for hitbox visualization */
#define PLAYER_HITBOX_COLOR 0, 255, 0, 255
#define WALL_HITBOX_COLOR 255, 255, 0, 255
#define ENEMY_HITBOX_COLOR 255, 0, 0, 255
#define ITEM_HITBOX_COLOR 0, 255, 255, 255
#define ENEMY_PROJECTILE_HITBOX_COLOR 255, 0, 255, 255
#define PLAYER_PROJECTILE_HITBOX_COLOR 0, 0, 255, 255

/**
 * @brief [Render] Renders all active hitboxes when debug mode is enabled
 * 
 * Iterates through all registered colliders and draws their hitboxes
 * with different colors based on their collision layer.
 */
void Debug_RenderHitboxes() {
    if (!app.config.debug) return;
    for (int i = 0; i < ColliderCount; i++) {
        Collider* collider = ColliderList[i];
        if (!collider) continue;
        if (!collider->active) continue;
        SDL_Rect hitbox = collider->hitbox;
        hitbox.x = Camera_WorldVecToScreen((Vec2) {hitbox.x, hitbox.y}).x;
        hitbox.y = Camera_WorldVecToScreen((Vec2) {hitbox.x, hitbox.y}).y;
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
            case COLLISION_LAYER_TRIGGER:
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
    for (int i = 0; i < MAX_INTERACTABLES; i++) {
        if (interactables[i].active) {
            SDL_Rect hitbox = Vec2_ToCenteredRect(interactables[i].position, interactables[i].hitboxSize);
            if (!Camera_WorldRectIsOnScreen(hitbox)) continue;

            hitbox = Vec2_ToCenteredRect(
                Camera_WorldVecToScreen(interactables[i].position),
                interactables[i].hitboxSize
            );
            SDL_SetRenderDrawColor(app.resources.renderer, ITEM_HITBOX_COLOR);
            SDL_RenderDrawRect(app.resources.renderer, &hitbox);
        }
    }
}

/**
 * @brief [Render] Renders the current FPS counter in the top-left corner
 * 
 * Creates and updates a text element showing the current frames per second.
 */
void Debug_RenderFPSCount() {
    if (!app.config.debug) return;
    // The UIElement struct stored in a static variable for reuse
    static UIElement* fpsTextElement = NULL;
    static UIElement* averageFpsTextElement = NULL;
    // Format FPS text
    char fpsText[16];
    sprintf(fpsText, "FPS: %d", app.state.fps);

    char averageFpsText[30];
    sprintf(averageFpsText, "Average FPS: %d", app.state.averageFps);

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

    if (!averageFpsTextElement) {
        // Create text element if it doesn't exist 

        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Rect renderRect = {10, 20, 0, 0};   
        float textScale = 1;
        UI_TextAlignment alignment = UI_TEXT_ALIGN_LEFT;

        averageFpsTextElement = UI_CreateText(
            averageFpsText, 
            renderRect, 
            textColor, 
            textScale, 
            alignment, 
            app.resources.textFont
        );
    } else {
        // Update text if it does exist.
        UI_ChangeText(averageFpsTextElement, averageFpsText);
    }

    // Update and render text
    UI_UpdateText(fpsTextElement);
    UI_RenderText(fpsTextElement);

    UI_UpdateText(averageFpsTextElement);
    UI_RenderText(averageFpsTextElement);
}

/**
 * @brief [Render] Renders a counter of frame spikes (frames exceeding target time)
 * 
 * Tracks and displays the number of frames that took longer than
 * the target frame time (frames with fps below 30).
 */
void Debug_RenderSpikeCount() {
    if (!app.config.debug) return;

    // The UIElement struct stored in a static variable for reuse
    static UIElement* spikeTextElement = NULL;
    
    // Count spike frames
    static int spikeCount = 0;
    float targetFPS = 30;
    if (Time->deltaTimeSeconds > 1.0 / targetFPS) spikeCount++;

    // Format text
    char text[20];
    sprintf(text, "Spike frames: %d", spikeCount);

    if (!spikeTextElement) {
        // Create text element if it doesn't exist 
        SDL_Color textColor = {255, 255, 255, 255};         // White color
        SDL_Rect renderRect = {10, 30, 0, 0};               // Position of the text (10, 30)
        float textScale = 1;                                // Text scale
        UI_TextAlignment alignment = UI_TEXT_ALIGN_LEFT;    // Text alignment

        spikeTextElement = UI_CreateText(
            text, 
            renderRect, 
            textColor, 
            textScale, 
            alignment, 
            app.resources.textFont
        );
    } else {
        // Update text if it does exist.
        UI_ChangeText(spikeTextElement, text);
    }

    UI_UpdateText(spikeTextElement);
    UI_RenderText(spikeTextElement);
}

/**
 * @brief [Render] Renders information about the current chunk the player is in
 * 
 * Shows the coordinates of the current chunk and the next chunk in the
 * main path.
 */
void Debug_RenderCurrentChunk() {
    if (!app.config.debug) return;
    // The UIElement struct stored in a static variable for reuse
    static UIElement* spikeTextElement = NULL;
    // Format text
    static int spikeCount = 0;
    float targetFPS = 30;
    if (Time->deltaTimeSeconds > 1.0 / targetFPS) spikeCount++;

    char text[20];

    Vec2 chunkPosition = Chunk_GetCurrentChunk(player.state.position)->position;
    int ChunkX = (int) chunkPosition.x;
    int ChunkY = (int) chunkPosition.y;

    int nextChunkX = testMap.mainPath[0].x;
    int nextChunkY = testMap.mainPath[0].y;
    for(int i = 0; i < MAP_LENGTH - 1; i++) {
        if (testMap.mainPath[i].x == ChunkX && testMap.mainPath[i].y == ChunkY) {
            nextChunkX = testMap.mainPath[i+1].x;
            nextChunkY = testMap.mainPath[i+1].y;
        }
    }   
    sprintf(text, "Player Position: (%d,%d)", (int) player.state.position.x, (int) player.state.position.y);

    if (!spikeTextElement) {
        // Create text element if it doesn't exist 

        SDL_Color textColor = {255, 255, 255, 255};
        SDL_Rect renderRect = {10, 40, 0, 0};   
        float textScale = 1;
        UI_TextAlignment alignment = UI_TEXT_ALIGN_LEFT;

        spikeTextElement = UI_CreateText(
            text, 
            renderRect, 
            textColor, 
            textScale, 
            alignment, 
            app.resources.textFont
        );
    } else {
        // Update text if it does exist.
        UI_ChangeText(spikeTextElement, text);
    }

    UI_UpdateText(spikeTextElement);
    UI_RenderText(spikeTextElement);
}