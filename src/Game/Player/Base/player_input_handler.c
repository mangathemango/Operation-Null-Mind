//? Written by Mango on 28/02/2025

#include <player.h>
#include <input.h>
#include <maps.h>

/**
 * @brief Processes player input for movement, skills and weapons
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

    if (Input->keyboard.keys[SDL_SCANCODE_1].pressed) Player_SwitchGun(&Gun_Pistol);
    if (Input->keyboard.keys[SDL_SCANCODE_2].pressed) Player_SwitchGun(&Gun_SMG);
    if (Input->keyboard.keys[SDL_SCANCODE_3].pressed) Player_SwitchGun(&Gun_AssaultRifle);
    if (Input->keyboard.keys[SDL_SCANCODE_4].pressed) Player_SwitchGun(&Gun_BattleRifle);
    if (Input->keyboard.keys[SDL_SCANCODE_5].pressed) Player_SwitchGun(&Gun_Shotgun);
    if (Input->keyboard.keys[SDL_SCANCODE_F].pressed && player.state.insideEnd) Map_Generate(), player.state.position.x = 4200, player.state.position.y = 4200;

    if (player.state.currentGun == NULL) {
        return;
    }

    if (player.state.currentGun->stats.fireMode == FIREMODE_AUTO) {
        if (Input->mouse.leftButton.held) Player_Shoot();
    } else {
        if (Input->mouse.leftButton.pressed) Player_Shoot();
    }
    
}