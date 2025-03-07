#include <debug.h>
#include <app.h>

/*
*   [Render?] Renders the hitbox of the player and walls.
*/
void Debug_RenderHitboxes() {
    // Draw player's hitbox (red)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &player->state.hitbox); 

    // Draw wall hitboxes
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int i = 0; i < environment.wallCount; i++) {
        Wall wall = environment.walls[i];
        SDL_RenderDrawRect(renderer, &wall.hitbox);
    }
}