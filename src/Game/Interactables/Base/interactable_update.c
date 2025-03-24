#include <interactable.h>
#include <player.h>
#include <input.h>

void Interactable_Update() {
    for (int i = 0; i < MAX_INTERACTABLES; i++) {
        if (interactables[i].active) {
            SDL_Rect hitbox = Vec2_ToCenteredRect(
                interactables[i].position, interactables[i].hitboxSize
            );
            if (SDL_HasIntersection(&player.state.collider.hitbox, &hitbox)) {
                interactables[i].interactable = true;
                if (Input->keyboard.keys[SDL_SCANCODE_E].pressed) {
                    interactables[i].callback(interactables[i].data, i);
                }
                break;
            } else {
                interactables[i].interactable = false;
            }
        }
    }
}