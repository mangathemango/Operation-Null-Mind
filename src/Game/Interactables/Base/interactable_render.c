#include <interactable.h>
#include <camera.h>
#include <stdio.h>
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

void Interactable_RenderInteractableHUD() {
    for (int i = 0; i < MAX_INTERACTABLES; i ++) {
        if (interactables[i].active && interactables[i].interactable) {
            UI_RenderText(interactionText);

            if (interactables[i].type == INTERACTABLE_ABILITIES) {
                static UIElement* abilityProText = NULL;
                static UIElement* abilityConText = NULL;
                static UIElement* abilityNameText = NULL;

                char abilityName[30];
                sprintf(abilityName, "[ %s ]", abilityData[*(int*)interactables[i].data].name);
                char abilityPro[50];
                sprintf(abilityPro, "[+] %s", abilityData[*(int*)interactables[i].data].descriptionPro);
                char abilityCon[50];
                sprintf(abilityCon, "[-] %s", abilityData[*(int*)interactables[i].data].descriptionCon);

                if (abilityNameText == NULL) {
                    abilityNameText = UI_CreateText(
                        abilityName,
                        (SDL_Rect) {
                            app.config.screen_width / 2,
                            10
                        },
                        (SDL_Color){255, 255, 255, 255},
                        1.0f,
                        UI_TEXT_ALIGN_CENTER,
                        app.resources.textFont
                    );
                } else {
                    UI_ChangeText(abilityNameText, abilityName);
                }
                UI_UpdateText(abilityNameText);
                UI_RenderText(abilityNameText);
                if (abilityProText == NULL) {
                    abilityProText = UI_CreateText(
                        abilityPro,
                        (SDL_Rect) {
                            app.config.screen_width / 2,
                            20
                        },
                        (SDL_Color){0, 255, 0, 255},
                        1.0f,
                        UI_TEXT_ALIGN_CENTER,
                        app.resources.textFont
                    );
                } else {
                    UI_ChangeText(abilityProText, abilityPro
                    );
                }
                UI_UpdateText(abilityProText);
                UI_RenderText(abilityProText);
                if (abilityConText == NULL) {
                    abilityConText = UI_CreateText(
                        abilityCon,
                        (SDL_Rect) {
                            app.config.screen_width / 2,
                            30
                        },
                        (SDL_Color){255, 0, 0, 255},
                        1.0f,
                        UI_TEXT_ALIGN_CENTER,
                        app.resources.textFont
                    );
                } else {
                    UI_ChangeText(abilityConText, abilityCon);
                }
                UI_UpdateText(abilityConText);
                UI_RenderText(abilityConText);
            }
            break;
        }
    }
}