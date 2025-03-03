#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>
#include <stdbool.h>
#include <player.h>

bool check_collision(const SDL_Rect* a, const SDL_Rect* b);
void prevent_movement(Player* player, const SDL_Rect* obstacle);

#endif