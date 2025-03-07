/*
    @file player_movement.c
*   This file contains the player's movement functions.
*/


#include <player.h>
#include <time_system.h>
#include <app.h>

/*
*   [PostUpdate?] Move the player in a direction.
?   @param direction The direction to move the player in.
    TODO: Normalize direction before moving the player.
    TODO: Use Vec2_Multiply and Vec2_Add instead of multiplying the x and y values manually.
*/
int Player_Move(Vec2 direction) {
    if (Vec2_Magnitude(direction) == 0) return 0;
    if (player.state.movementLocked) return 0;
    player.state.direction = Vec2_Add(player.state.direction, direction);
    player.state.moving = true;
    player.state.position.x += direction.x * (player.stats.walkSpeed * Time->deltaTimeSeconds);
    player.state.position.y += direction.y * (player.stats.walkSpeed * Time->deltaTimeSeconds);
    
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