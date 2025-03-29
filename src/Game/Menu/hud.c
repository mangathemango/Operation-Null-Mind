#include <hud.h>
#include <app.h>
#include <UI_text.h>
#include <string.h>
#include <minimap.h>
#include <stdio.h>
#include <interactable.h>

static SDL_Texture* healthTexture;
static SDL_Texture* ammoTexture;
Vec2 barSize = {120, 14};
Vec2 iconSize = {10, 10};
float barX = 10;
float iconX = 22;


void HUD_Start() {
    healthTexture = IMG_LoadTexture(app.resources.renderer, "Assets/Images/Icons/health.png");
    ammoTexture = IMG_LoadTexture(app.resources.renderer, "Assets/Images/Icons/ammo.png");
}

void HUD_RenderHealthBar() {
    Vec2 healthBarPosition = (Vec2) {barX, app.config.screen_height - 42};
    SDL_Rect borderDest = Vec2_ToRect(healthBarPosition, barSize);
    SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(app.resources.renderer, &borderDest);

    SDL_Rect fillingDest = Vec2_ToRect(
        Vec2_Add(healthBarPosition, (Vec2) {1.0f, 1.0f}),
        Vec2_Subtract(barSize, (Vec2) {2.0f, 2.0f}) 
    );
    SDL_SetRenderDrawColor(app.resources.renderer, 54, 54, 54, 255);
    SDL_RenderFillRect(app.resources.renderer, &fillingDest);

    static float currentBarWidth = 0;
    currentBarWidth += (player.state.currentHealth - currentBarWidth) * 0.1f;
    SDL_Rect barDest = Vec2_ToRect(
        healthBarPosition, 
        (Vec2) {
            barSize.x * (currentBarWidth / (float) player.stats.maxHealth), 
            barSize.y
        }
    );
    SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(app.resources.renderer, &barDest);

    

    SDL_Rect iconDest = (SDL_Rect) {
        healthBarPosition.x + (barSize.x - iconSize.x) - 5, 
        healthBarPosition.y + (barSize.y - iconSize.y) / 2, 
        10,
        10
    };
    SDL_RenderCopy(app.resources.renderer, healthTexture, NULL, &iconDest);

    static UIElement* healthTextElement = NULL;
    char healthText[10];
    sprintf(healthText, "%d", player.state.currentHealth);
    if (!healthTextElement) {
        healthTextElement = UI_CreateText(
            healthText, 
            (SDL_Rect) {
                healthBarPosition.x + 5, 
                healthBarPosition.y, 
                0, 
                0
            }, 
            (SDL_Color) {139, 139, 139, 255}, 
            1.0f, 
            UI_TEXT_ALIGN_LEFT, 
            app.resources.textFont
        );
    } else {
        UI_ChangeText(healthTextElement, healthText);
    }
    UI_UpdateText(healthTextElement);
    UI_RenderText(healthTextElement);
}

void HUD_RenderAmmoBar() {
    Vec2 ammoBarPosition = (Vec2) {barX, app.config.screen_height - 25};    
    SDL_Rect borderDest = Vec2_ToRect(ammoBarPosition, barSize);
    SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(app.resources.renderer, &borderDest);

    SDL_Rect fillingDest = Vec2_ToRect(
        Vec2_Add(ammoBarPosition, (Vec2) {1.0f, 1.0f}),
        Vec2_Subtract(barSize, (Vec2) {2.0f, 2.0f}) 
    );
    SDL_SetRenderDrawColor(app.resources.renderer, 54, 54, 54, 255);
    SDL_RenderFillRect(app.resources.renderer, &fillingDest);
    
    static float currentBarWidth = 0;
    currentBarWidth += (player.state.currentAmmo - currentBarWidth) * 0.1f;
    SDL_Rect barDest = Vec2_ToRect(
        ammoBarPosition, 
        (Vec2) {
            barSize.x * currentBarWidth / (float) player.stats.maxAmmo, 
            barSize.y
        }
    );
    SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(app.resources.renderer, &barDest);
    SDL_Rect iconDest = (SDL_Rect) {
        ammoBarPosition.x + (barSize.x - iconSize.x) - 5, 
        ammoBarPosition.y + (barSize.y - iconSize.y) / 2, 
        10,
        10
    };
    SDL_RenderCopy(app.resources.renderer, ammoTexture, NULL, &iconDest);

    static UIElement* ammoTextElement = NULL;
    char ammoText[10];
    sprintf(ammoText, "%d", player.state.currentAmmo);
    if (!ammoTextElement) {
        ammoTextElement = UI_CreateText(
            ammoText, 
            (SDL_Rect) {
                ammoBarPosition.x + 5, 
                ammoBarPosition.y, 
                0, 
                0
            }, 
            (SDL_Color) {139, 139, 139, 255}, 
            1.0f, 
            UI_TEXT_ALIGN_LEFT, 
            app.resources.textFont
        );
    } else {
        UI_ChangeText(ammoTextElement, ammoText);
    }
    UI_UpdateText(ammoTextElement);
    UI_RenderText(ammoTextElement);
}

void HUD_RenderCurrentGun() {
    GunData gun = player.state.currentGun;
    SDL_Texture* gunTexture = gun.resources.animation->spritesheet;
    SDL_Rect srcRect = {0, 0, gun.animData.frameSize.x, gun.animData.frameSize.y};
    SDL_Rect destRect = {
        app.config.screen_width - 20 - gun.animData.frameSize.x * 2, 
        app.config.screen_height - 60 - gun.animData.frameSize.y, 
        gun.animData.frameSize.x * 2, 
        gun.animData.frameSize.y * 2
    };
    SDL_RenderCopyEx(app.resources.renderer, gunTexture, &srcRect, &destRect, 0 , NULL, SDL_FLIP_HORIZONTAL);
    static UIElement* gunNameTextElement = NULL;
    char gunName[30];
    strcpy(gunName, gun.name);
    if (!gunNameTextElement) {
        gunNameTextElement = UI_CreateText(
            gunName, (SDL_Rect) {
                app.config.screen_width - 20, 
                app.config.screen_height - 50, 
                0, 
                0
            }, 
            (SDL_Color) {255, 255, 255, 255}, 
            1.0f, 
            UI_TEXT_ALIGN_RIGHT, 
            app.resources.textFont
        );
    } else {
        UI_ChangeText(gunNameTextElement, gunName);
    }
    UI_UpdateText(gunNameTextElement);
    UI_RenderText(gunNameTextElement);
}

void HUD_RenderAmmoDisplay() {
    static UIElement* ammoTextElement = NULL;
    char ammoText[4] = "--";
    int currentAmmo = player.state.currentGun.state.currentAmmo;
    if (!ammoTextElement) {
        ammoTextElement = UI_CreateText(
            ammoText, 
            (SDL_Rect) {
                app.config.screen_width - 20, 
                app.config.screen_height - 38, 
                0, 
                0
            }, 
            (SDL_Color) {255, 255, 255, 255}, 
            3.0f, 
            UI_TEXT_ALIGN_RIGHT, 
            app.resources.textFont
        );
    } else {
        UI_ChangeText(ammoTextElement, ammoText);
    }
    UI_UpdateText(ammoTextElement);
    UI_RenderText(ammoTextElement);


    static UIElement* fireModeTextElement = NULL;
    char fireModeText[10];
    if (player.state.currentGun.stats.fireMode == FIREMODE_SEMI) {
        strcpy(fireModeText, "SEMI");
    } else {
        strcpy(fireModeText, "AUTO");
    }
    if (!fireModeTextElement) {
        fireModeTextElement = UI_CreateText(
            fireModeText, 
            (SDL_Rect) {
                app.config.screen_width - 62, 
                app.config.screen_height - 32, 
                0, 
                0
            }, 
            (SDL_Color) {200, 200, 200, 255}, 
            1.0f, 
            UI_TEXT_ALIGN_RIGHT, 
            app.resources.textFont
        );
    } else {
        UI_ChangeText(fireModeTextElement, fireModeText);
    }
    UI_UpdateText(fireModeTextElement);
    UI_RenderText(fireModeTextElement);

    static UIElement* ammoConsumptionTextElement = NULL;
    char ammoConsumptionText[10];
    sprintf(ammoConsumptionText, "%dX", player.state.currentGun.stats.ammoConsumption);
    if (!ammoConsumptionTextElement) {
        ammoConsumptionTextElement = UI_CreateText(
            ammoConsumptionText, 
            (SDL_Rect) {
                app.config.screen_width - 70, 
                app.config.screen_height - 18, 
                0, 
                0
            }, 
            (SDL_Color) {200, 200, 200, 255}, 
            1.0f, 
            UI_TEXT_ALIGN_RIGHT, 
            app.resources.textFont
        );
    } else {
        UI_ChangeText(ammoConsumptionTextElement, ammoConsumptionText);
    }
    UI_UpdateText(ammoConsumptionTextElement);
    UI_RenderText(ammoConsumptionTextElement);

    SDL_Rect dest = (SDL_Rect) {
        app.config.screen_width - 70, 
        app.config.screen_height - 17, 
        10, 
        10
    };
    SDL_RenderCopy(app.resources.renderer, ammoTexture, NULL, &dest);
}

void HUD_RenderCurrentLevel() {
    static UIElement* levelTextElement = NULL;
    char levelText[30];
    sprintf(levelText, "Stage %d", game.currentStage);
    if (!levelTextElement) {
        levelTextElement = UI_CreateText(
            levelText, 
            (SDL_Rect) {
                app.config.screen_width - MINIMAP_SIZE / 2 - 10,
                MINIMAP_SIZE + 15,
            }, 
            (SDL_Color) {255, 255, 255, 255}, 
            1.0f, 
            UI_TEXT_ALIGN_CENTER, 
            app.resources.textFont
        );
    } else {
        UI_ChangeText(levelTextElement, levelText);
    }
    UI_UpdateText(levelTextElement);
    UI_RenderText(levelTextElement);
}

void HUD_Render() {
    HUD_RenderHealthBar();
    HUD_RenderAmmoBar();
    HUD_RenderCurrentGun();
    HUD_RenderCurrentLevel();
    HUD_RenderAmmoDisplay();
    if (hasInteraction) {
        UI_RenderText(interactionText);
    }
}