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
            SDL_RenderCopy(app.resources.renderer, interactables[i].spriteTexture, NULL, &dest);
            
            
            if (interactables[i].interactable) {
                SDL_QueryTexture(interactables[i].textTexture, NULL, NULL, &dest.w, &dest.h);
                dest.x -= (dest.w - interactables[i].renderSize.x) / 2;
                dest.y -= 10;
                SDL_RenderCopy(app.resources.renderer, interactables[i].textTexture, NULL, &dest);
            }
        }
    }
}