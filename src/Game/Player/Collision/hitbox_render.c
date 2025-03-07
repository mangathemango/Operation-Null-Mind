//This is for creating hitbox for player and environment and updating them.
#include <SDL.h>
#include <player.h>
#include <environment.h>
#include <app.h>
//Should call them in the app_render.c
//Function for rendering the hitbox of the player
void Render_PlayerHitbox(SDL_Renderer* renderer, PlayerData* player) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);//invisible player hitbox
    SDL_RenderDrawRect(renderer, &player->state.hitbox);
}
//Function for rendering the hitbox of the wall
void Render_WallHitboxes(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); //invisible wall hitbox
    for (int i = 0; i < environment.wallCount; i++) {
        Wall wall = environment.walls[i];
        SDL_RenderDrawRect(renderer, &wall.hitbox);
    }
}
