#include <interactable.h>
#include <player.h>

void Interactable_Update() {
    for (int i = 0; i < MAX_INTERACTABLES; i++) {
        if (interactables[i].active) {
            SDL_Rect hitbox = Vec2_ToCenteredRect(
                interactables[i].position, interactables[i].hitboxSize
            );
            if (SDL_HasIntersection(
                &player.state.collider.hitbox, &hitbox
            )) {
                interactables[i].interactable = true;
                break;
            } else {
                interactables[i].interactable = false;
            }
        }
    }
}