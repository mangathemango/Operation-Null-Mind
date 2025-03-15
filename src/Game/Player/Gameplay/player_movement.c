/*
    @file player_movement.c
*   This file contains the player's movement functions.

?   Written by Mango on 03/03/2025
*/


#include <player.h>
#include <time_system.h>
#include <app.h>
#include <input.h>
#include <colliders.h>

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
*/
int Player_Move() {
    if (player.state.currentSpeed == 0) return 0;
    if (Vec2_Magnitude(player.state.direction) == 0) return 0;

    player.state.direction = Vec2_Normalize(player.state.direction);

    Vec2 oldPosition = player.state.position;

    player.state.position.x += player.state.direction.x * player.state.currentSpeed * Time->deltaTimeSeconds;
    Player_UpdateHitbox();
    if (Player_DetectCollision()) player.state.position.x = oldPosition.x;
    
    player.state.position.y += player.state.direction.y * player.state.currentSpeed * Time->deltaTimeSeconds;
    Player_UpdateHitbox();
    if (Player_DetectCollision()) player.state.position.y = oldPosition.y;

    if (player.state.position.x != oldPosition.x || player.state.position.y != oldPosition.y) {
        player.state.moving = true;
    } else {
        player.state.moving = false;
    }
    

    return 0;
}


void Player_UpdateHitbox() {
    player.state.collider.hitbox.x = player.state.position.x - player.animData.spriteSize.x / 2 + 5; 
    player.state.collider.hitbox.y = player.state.position.y - player.animData.spriteSize.y / 2 + 5;
}