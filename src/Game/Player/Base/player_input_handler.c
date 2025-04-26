/**
 * @file player_input_handler.c
 * @brief Processes player input for character control
 *
 * Handles keyboard and mouse input for movement, weapon
 * switching, attacks, and ability activation.
 *
 * @author Mango
 * @date 2025-02-28
 */

//? Written by Mango on 28/02/2025

#include <player.h>
#include <input.h>
#include <maps.h>
#include <chunks.h>
#include <interactable.h>
#include <settings.h>

/**
 * @brief [Event Handler] Processes player input for movement, skills and weapons
 * 
 * Checks keyboard and mouse input to trigger player actions including
 * movement, dashing, weapon switching, and shooting.
 */
void Player_Input_Handler() {
    if (game.viewingLog >= 0) {
        if (Input->anyKey.pressed || Input->mouse.leftButton.pressed) {
            game.viewingLog = -1;
        }
        return;
    }

    // Movement
    if (Input_IsActionHeld(ACTION_MOVE_UP))     Player_Look(Vec2_Up);
    if (Input_IsActionHeld(ACTION_MOVE_LEFT))   Player_Look(Vec2_Left);
    if (Input_IsActionHeld(ACTION_MOVE_DOWN))   Player_Look(Vec2_Down);
    if (Input_IsActionHeld(ACTION_MOVE_RIGHT))  Player_Look(Vec2_Right);

    // Actions
    if (Input_IsActionPressed(ACTION_DASH)) Player_Dash();
    if (Input_IsActionPressed(ACTION_SWITCH_GUN)) Player_SwitchGun(0);

    // Shooting based on fire mode
    if (player.state.currentGun.stats.fireMode == FIREMODE_AUTO) {
        if (Input_IsActionHeld(ACTION_SHOOT)) Player_Shoot();
    } else if (player.state.currentGun.stats.fireMode == FIREMODE_BURST) {
        static int burstCount = 0;
        static float burstTimer = 0.0f;
        if (Input_IsActionPressed(ACTION_SHOOT)) {
            burstCount = player.state.currentGun.stats.bulletsPerShot;
            burstTimer = 0.0f;
        }
        if (burstCount > 0) {
            burstTimer -= Time->deltaTimeSeconds;
            if (burstTimer <= 0.0f) {
                Player_Shoot();
                burstCount--;
                burstTimer = 60.0f / player.state.currentGun.stats.fireRate;
            }
        }
    } else {
        if (Input_IsActionPressed(ACTION_SHOOT)) Player_Shoot();
    }

    if (Input_IsActionPressed(ACTION_PARRY)) Player_Parry();
    if (Input_IsActionPressed(ACTION_TOGGLE_HUD)) game.hudToggled = !game.hudToggled;
}