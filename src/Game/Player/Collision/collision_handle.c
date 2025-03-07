#include <environment.h>
#include <player.h>
#include <app.h>
#include <input.h>

void Update_Player(PlayerData *player) {
    // Store previous position in case of collision
    float prevx = player->state.position.x;
    float prevy = player->state.position.y;

    // Calculate new position
    float newx = player->state.position.x + player->state.direction.x * player->config.speed * app.time.deltaTime;
    float newy = player->state.position.y + player->state.direction.y * player->config.speed * app.time.deltaTime;

    // Create test hitbox for collision detection
    SDL_Rect testHitbox = {
        .x = (int)(newx - player->state.hitbox.w / 2),
        .y = (int)(newy - player->state.hitbox.h / 2),
        .w = player->state.hitbox.w,
        .h = player->state.hitbox.h
    };

    // Check for collisions with all walls
    bool collision = false;
    for (int i = 0; i < environment.wallCount; i++) {
        Wall wall = environment.walls[i];
        int collisionFlag = 0;
        Check_Collision(testHitbox, wall.hitbox, &collisionFlag);
        
        if (collisionFlag) {
            collision = true;
            // Completely stop movement on collision
            player->state.position.x = prevx;
            player->state.position.y = prevy;
            player->state.direction.x = 0;
            player->state.direction.y = 0;

            player->state.moving = false;  // Ensure moving state is false
            // Keep hitbox at previous position
            player->state.hitbox.x = (int)(prevx - player->state.hitbox.w / 2);
            player->state.hitbox.y = (int)(prevy - player->state.hitbox.h / 2);
            break;
        }
    }

    // Only update position if no collision occurred
    if (!collision) {
        player->state.position.x = newx;
        player->state.position.y = newy;
        player->state.hitbox.x = (int)(newx - player->state.hitbox.w / 2);
        player->state.hitbox.y = (int)(newy - player->state.hitbox.h / 2);
    }

    // Update moving state
    player->state.moving = (player->state.direction.x != 0 || player->state.direction.y != 0);
}