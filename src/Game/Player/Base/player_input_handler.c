#include <player.h>
#include <input.h>

/*
*   This function handles the player's input.
*/
void Player_Input_Handler() {

    if (Input->keyboard.keys[SDL_SCANCODE_W].held) Player_Move(Vec2_Up);
    if (Input->keyboard.keys[SDL_SCANCODE_A].held) Player_Move(Vec2_Left);
    if (Input->keyboard.keys[SDL_SCANCODE_S].held) Player_Move(Vec2_Down);
    if (Input->keyboard.keys[SDL_SCANCODE_D].held) Player_Move(Vec2_Right);
    if (Input->keyboard.keys[SDL_SCANCODE_LSHIFT].pressed) Player_Dash();

    if (Input->keyboard.keys[SDL_SCANCODE_1].pressed) player.state.currentGun = GUN_PISTOL;
    if (Input->keyboard.keys[SDL_SCANCODE_2].pressed) player.state.currentGun = GUN_SHOTGUN;
    if (Input->keyboard.keys[SDL_SCANCODE_3].pressed) player.state.currentGun = GUN_SMG;
    if (Input->keyboard.keys[SDL_SCANCODE_4].pressed) player.state.currentGun = GUN_ASSAULT_RIFLE;
    if (Input->keyboard.keys[SDL_SCANCODE_5].pressed) player.state.currentGun = GUN_BATTLE_RIFLE;
}