#include <interactable.h>
#include <camera.h>
#include <app.h>

void Interactable_Render() {
    for (int i = 0; i < MAX_INTERACTABLES; i++) {
        if (interactables[i].active) {
            SDL_Rect dest =  Vec2_ToCenteredRect(
                Camera_WorldVecToScreen(interactables[i].position),
                interactables[i].renderSize
            );
            SDL_Rect* srcRect = (interactables[i].srcRect.x >= 0) ? &interactables[i].srcRect : NULL;
            SDL_RenderCopy(app.resources.renderer, interactables[i].spriteTexture, srcRect, &dest);
        }
    }
}

void Interactable_RenderEndRoom() {
    for (int i = 0; i < MAX_INTERACTABLES; i++) {
        if (interactables[i].active && interactables[i].type == INTERACTABLE_EXIT) {
            SDL_Rect dest =  Vec2_ToCenteredRect(
                Camera_WorldVecToScreen(interactables[i].position),
                (Vec2) {120, 80}
            );
            dest.h = 50;
            SDL_Rect src = {0, 0, 120, 50};
            SDL_RenderCopy(app.resources.renderer, interactables[i].spriteTexture, &src, &dest);
            break;
        }
    }
}

void Interactable_RenderInteractionText() {
    for (int i = 0; i < MAX_INTERACTABLES; i++) {
        if (interactables[i].active && interactables[i].interactable) {
            int sizex, sizey;
            SDL_QueryTexture(interactables[i].textTexture, NULL, NULL, &sizex, &sizey);
            SDL_Rect dest = Vec2_ToCenteredRect(
                Camera_WorldVecToScreen(
                    (Vec2) {
                        interactables[i].position.x,
                        interactables[i].position.y - 20
                    }
                ),
                (Vec2) {sizex, sizey}
            );
            SDL_RenderCopy(app.resources.renderer, interactables[i].textTexture, NULL, &dest);
            break;
        }
    }
}