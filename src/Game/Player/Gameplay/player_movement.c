/*
    @file player_movement.c
*   This file contains the player's movement functions.

?   Written by Mango on 03/03/2025
*/


#include <player.h>
#include <time_system.h>
#include <app.h>
#include <environment.h>
#include <input.h>
#include <collision.h>

/*
*   [PostUpdate?] Move the player in a direction.
?   @param direction The direction to move the player in.
    TODO: Normalize direction before moving the player.
    TODO: Use Vec2_Multiply and Vec2_Add instead of multiplying the x and y values manually.
*/
int Player_Look(Vec2 direction) {
    if (player.state.directionLocked) return 0;
    Vec2_Increment(&player.state.direction, direction); 
    player.state.currentSpeed = player.stats.walkSpeed;
    return 0;
}


/*
*   Move the player in a direction.
?   @param direction The direction to move the player in.
    TODO: Normalize direction before moving the player.
    TODO: Use Vec2_Multiply and Vec2_Add instead of multiplying the x and y values manually.
*/
int Player_Move() {
    if (player.state.currentSpeed == 0) return 0;
    player.state.hitbox = (SDL_Rect) {
        player.state.position.x - player.animData.spriteSize.x / 2,
        player.state.position.y - player.animData.spriteSize.y / 2,
        player.animData.spriteSize.x,
        player.animData.spriteSize.y
    };
    if (Player_DetectCollision()) return 0;
    player.state.moving = true;
    Vec2_Increment(&player.state.position,
                    Vec2_Multiply(player.state.direction, player.state.currentSpeed * Time->deltaTimeSeconds));
    Player_WrapAroundScreen();

    return 0;
}


/* 
*   [PostUpdate] Teleport the player to the other side of the screen if they go off-screen.
!   This is just for temporary player movement debugging, and will be removed later.
*/
void Player_WrapAroundScreen()
{
    //This is the logic for the player to wrap around the screen.
    if (player.state.position.x >= app.config.screen_width) {
        player.state.position.x = 0;
    }
    else if (player.state.position.x <= 0) {
        player.state.position.x = app.config.screen_width;
    }
    if (player.state.position.y >= app.config.screen_height) {
        player.state.position.y = -10; //Because the height should come from below 0
    }
    else if (player.state.position.y <= -10) {
        player.state.position.y = app.config.screen_height;
    }
}

bool Player_DetectCollision() {
    Vec2 newPosition = Vec2_Add(player.state.position, Vec2_Multiply(
        player.state.direction,
        player.state.currentSpeed * Time->deltaTimeSeconds
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
        if (collisionFlag) return true;
    }
    return false;
}