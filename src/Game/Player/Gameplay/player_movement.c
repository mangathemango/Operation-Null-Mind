/**
 * @file player_movement.c
 * @brief Handles player character movement
 *
 * Contains functions for moving the player character,
 * handling acceleration, and managing movement states.
 *
 * @author Mango
 * @date 2025-03-03
 */

#include <player.h>
#include <time_system.h>
#include <app.h>
#include <input.h>
#include <colliders.h>

/**
 * @brief [Utility] Sets the player's movement direction
 * 
 * Updates the player's direction vector and sets appropriate movement speed.
 * Ignores input if the direction is locked (e.g., during a dash).
 * 
 * @param direction The direction to move the player in
 * @return int Status code (0 for success)
 * 
 * @todo Normalize direction before moving the player.
 * @todo Use Vec2_Multiply and Vec2_Add instead of multiplying the x and y values manually.
 */
int Player_Look(Vec2 direction) {
    if (player.state.directionLocked) return 0;
    Vec2_Increment(&player.state.direction, direction); 
    player.state.currentSpeed = player.stats.walkSpeed;
    return 0;
}

/**
 * @brief [PostUpdate] Moves the player according to current direction and speed
 * 
 * Applies the player's direction and speed to position, handles collision checking,
 * and updates movement state flags.
 * 
 * @return int Status code (0 for success)
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

/**
 * @brief [Utility] Updates the player's hitbox position based on current position
 * 
 * Recalculates the position of the player's collision hitbox to match
 * their current world position, with appropriate offsets.
 */
void Player_UpdateHitbox() {
    player.state.collider.hitbox.x = player.state.position.x - player.animData.spriteSize.x / 2 + 5; 
    player.state.collider.hitbox.y = player.state.position.y - player.animData.spriteSize.y / 2 + 5;
}