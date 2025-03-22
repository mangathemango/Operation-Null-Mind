/**
 * @file player_animations.c
 * @brief Player animation system implementation
 *
 * Manages player character animations based on state and actions.
 * Handles animation transitions, updates, and initialization.
 * 
 * @author Mango
 * @date 2025-03-07
 */

//? Written by Mango on 07/03/2025

#include <player.h>
#include <app.h>

/**
 * @brief [Start] Initializes the player's animation system
 * 
 * Creates and sets up the player's animation system from the
 * animation data defined in player_data.c.
 * 
 * @return int Status code (0 for success, 1 for error)
 */
int Player_AnimationInit() {
    player.resources.animation = Animation_Create(&player.animData);
    if (!player.resources.animation) {
        SDL_Log("Failed to create player animation");
        return 1;
    }
    return 0;
}

/**
 * @brief [PostUpdate] Updates the player's animation state
 * 
 * Selects the appropriate animation based on player state
 * (idle or walking) and advances the animation frames.
 * 
 * @return int Status code (0 for success)
 */
int Player_AnimationUpdate() {
    if (player.state.moving) {
        Animation_Play(player.resources.animation, "walk");
    } else {
        Animation_Play(player.resources.animation, "idle");
    }
    Animation_Update(player.resources.animation);
    return 0;
}