#include "player.h"
#include <SDL.h>

void init_player(Player* player) {
    player->position = (SDL_FRect){100, 100, 32, 32};
    player->hitbox = (SDL_Rect){100, 100, 32, 32};
    player->move_speed = 5.0f;
}

void handle_input(Player* player, const Uint8* keystate) {
    player->position.x += keystate[SDL_SCANCODE_D] ? player->move_speed :
                          keystate[SDL_SCANCODE_A] ? -player->move_speed : 0;
    player->position.y += keystate[SDL_SCANCODE_S] ? player->move_speed :
                          keystate[SDL_SCANCODE_W] ? -player->move_speed : 0;
}

void update_player(Player* player) {
    // Update hitbox position to match player position
    player->hitbox.x = (int)player->position.x;
    player->hitbox.y = (int)player->position.y;
}

void render_player(Player* player, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRectF(renderer, &player->position);
}