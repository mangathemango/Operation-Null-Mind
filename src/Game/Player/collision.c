#include "hitbox.h"

bool check_collision(const SDL_Rect* a, const SDL_Rect* b) {
    return SDL_HasIntersection(a, b);
}

void prevent_movement(Player* player, const SDL_Rect* obstacle) {
    SDL_Rect future_hitbox = player->hitbox;
    
    // Check horizontal movement
    future_hitbox.x = (int)player->position.x;
    if (check_collision(&future_hitbox, obstacle)) {
        player->position.x = player->hitbox.x;
    }
    
    // Check vertical movement
    future_hitbox.y = (int)player->position.y;
    if (check_collision(&future_hitbox, obstacle)) {
        player->position.y = player->hitbox.y;
    }
}