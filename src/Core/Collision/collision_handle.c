#include <environment.h>
#include <player.h>
#include <app.h>
#include <input.h>
#include <time_system.h>
#include <collision.h>

bool Player_DetectCollision() {
    Vec2 newPosition = Vec2_Add(player.state.position, Vec2_Multiply(
        player.state.direction,
        player.config.speed * Time->deltaTimeSeconds
    ));
    // Create test hitbox for collision detection
    SDL_Rect testHitbox = {
        .x = (int)(newPosition.x - player.state.hitbox.w / 2),
        .y = (int)(newPosition.y - player.state.hitbox.h / 2),
        .w = player.state.hitbox.w,
        .h = player.state.hitbox.h
    };

    for (int i = 0; i < environment.wallCount; i++) {
        Wall wall = environment.walls[i];
        int collisionFlag = 0;
        Check_Collision(testHitbox, wall.hitbox, &collisionFlag);
        if (collisionFlag) {
                // Completely stop movement on collision
                player.state.direction = Vec2_Zero;

                player.state.moving = false;  // Ensure moving state is false
                return true;
        }
    }

    // Update moving state
    player.state.moving = (player.state.direction.x != 0 || player.state.direction.y != 0);

    return false;
}