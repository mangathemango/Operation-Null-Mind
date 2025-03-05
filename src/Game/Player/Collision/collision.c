// To check whether they're colliding or not
#include <player.h>
#include <environment.h>

void Check_Collision(SDL_Rect a, SDL_Rect b, int *collisionFlag) {
    if (a.x + a.w > b.x && a.x < b.x + b.w &&
        a.y + a.h > b.y && a.y < b.y + b.h) {
        *collisionFlag = 1;
    } else {
        *collisionFlag = 0;
    }
}