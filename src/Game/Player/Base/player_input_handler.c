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

/**
 * @brief [Event Handler] Processes player input for movement, skills and weapons
 * 
 * Checks keyboard and mouse input to trigger player actions including
 * movement, dashing, weapon switching, and shooting.
 */
void Player_Input_Handler() {

    if (Input->keyboard.keys[SDL_SCANCODE_W].held || 
        Input->keyboard.keys[SDL_SCANCODE_UP].held)     Player_Look(Vec2_Up);
    if (Input->keyboard.keys[SDL_SCANCODE_A].held || 
        Input->keyboard.keys[SDL_SCANCODE_LEFT].held)   Player_Look(Vec2_Left);
    if (Input->keyboard.keys[SDL_SCANCODE_S].held ||
        Input->keyboard.keys[SDL_SCANCODE_DOWN].held)   Player_Look(Vec2_Down);
    if (Input->keyboard.keys[SDL_SCANCODE_D].held ||
        Input->keyboard.keys[SDL_SCANCODE_RIGHT].held)  Player_Look(Vec2_Right);

    if (Input->keyboard.keys[SDL_SCANCODE_LSHIFT].pressed) Player_Dash();

    if (Input->keyboard.keys[SDL_SCANCODE_LCTRL].pressed) Player_CrashOut();

    if (Input->keyboard.keys[SDL_SCANCODE_Q].pressed) Player_SwitchGun(0);
    
    if (Input->keyboard.keys[SDL_SCANCODE_F].pressed) {
        Vec2 chunkPosition = testMap.mainPath[testMap.mainPathLength];
        player.state.position = Chunk_GetChunkCenter(&testMap.chunks[(int) chunkPosition.x][(int) chunkPosition.y]);
    }

    if (player.state.currentGun.stats.fireMode == FIREMODE_AUTO) {
        if (Input->mouse.leftButton.held) Player_Shoot();
    } else {
        if (Input->mouse.leftButton.pressed) Player_Shoot();
    }

    if(Input->mouse.rightButton.pressed) Parry();

    if (Input->keyboard.keys[SDL_SCANCODE_TAB].pressed) game.hudToggled = !game.hudToggled;
    
    if (Input->mouse.leftButton.pressed) {
        game.viewingLog = -1;
    }
}