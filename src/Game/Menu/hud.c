#include <hud.h>
#include <app.h>
#include <UI_text.h>
#include <string.h>
#include <minimap.h>
#include <stdio.h>
#include <interactable.h>
#include <player.h>

static SDL_Texture* healthTexture;
static SDL_Texture* ammoTexture;
Vec2 barSize = {120, 14};
Vec2 iconSize = {10, 10};
float barX = 10;
float iconX = 22;


void HUD_Start() {
    // Load textures once and check for errors
    healthTexture = IMG_LoadTexture(app.resources.renderer, "Assets/Images/Icons/health.png");
    if (!healthTexture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load health texture: %s", SDL_GetError());
    }

    ammoTexture = IMG_LoadTexture(app.resources.renderer, "Assets/Images/Icons/ammo.png");
    if (!ammoTexture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load ammo texture: %s", SDL_GetError());
    }
}

void HUD_RenderBar(Vec2 position, float value, float maxValue, SDL_Texture* icon, const char* text) {
    // Border
    SDL_Rect borderDest = Vec2_ToRect(position, barSize);
    SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(app.resources.renderer, &borderDest);

    // Background
    SDL_Rect fillingDest = Vec2_ToRect(
        Vec2_Add(position, (Vec2) {1.0f, 1.0f}),
        Vec2_Subtract(barSize, (Vec2) {2.0f, 2.0f})
    );
    SDL_SetRenderDrawColor(app.resources.renderer, 54, 54, 54, 255);
    SDL_RenderFillRect(app.resources.renderer, &fillingDest);

    // Filled portion
    SDL_Rect barDest = Vec2_ToRect(
        position, 
        (Vec2) {
            barSize.x * (value / maxValue), 
            barSize.y
        }
    );
    SDL_SetRenderDrawColor(app.resources.renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(app.resources.renderer, &barDest);

    // Icon
    SDL_Rect iconDest = (SDL_Rect) {
        position.x + (barSize.x - iconSize.x) - 5, 
        position.y + (barSize.y - iconSize.y) / 2, 
        iconSize.x,
        iconSize.y
    };
    SDL_RenderCopy(app.resources.renderer, icon, NULL, &iconDest);

    // Text - Create a unique text element for each bar based on position
    // Health bar is at app.config.screen_height - 42
    // Ammo bar is at app.config.screen_height - 25
    static UIElement* healthTextElement = NULL;
    static UIElement* ammoTextElement = NULL;
    
    UIElement** textElement = NULL;
    
    // Determine which text element to use based on the Y position
    if(position.y >= app.config.screen_height - 42 && position.y < app.config.screen_height - 30) {
        textElement = &healthTextElement;
    } else {
        textElement = &ammoTextElement;
    }
    
    if(!*textElement) {
        *textElement = UI_CreateText(
            text, 
            (SDL_Rect) {
                position.x + 5, 
                position.y, 
                0, 
                0
            }, 
            (SDL_Color) {139, 139, 139, 255}, 
            1.0f, 
            UI_TEXT_ALIGN_LEFT, 
            app.resources.textFont
        );
    } else {
        UI_ChangeText(*textElement, text);
    }
    UI_UpdateText(*textElement);
    UI_RenderText(*textElement);
}

void HUD_RenderHealthBar() {
    char healthText[10];
    sprintf(healthText, "%d", player.state.currentHealth);
    HUD_RenderBar(
        (Vec2) {barX, app.config.screen_height - 42}, 
        player.state.currentHealth, 
        player.stats.maxHealth, 
        healthTexture, 
        healthText
    );
}

void HUD_RenderAmmoBar() {
    char ammoText[10];
    sprintf(ammoText, "%d", player.state.currentAmmo);
    HUD_RenderBar(
        (Vec2) {barX, app.config.screen_height - 25}, 
        player.state.currentAmmo, 
        player.stats.maxAmmo, 
        ammoTexture, 
        ammoText
    );
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

void HUD_RenderPixilFrame() {
    //Okay just in case you wanna change anything in this code, ill explain
    //however in theory it should be simple

    // This is the AssetPath, self-explantory, the enum for skills is in player.h
    char* AssetPath[TOTAL_SKILLS] = {
        [ARMORED_UP] = "Assets/Images/Icons/abilities/shieldUp.png",
        [GHOST_LOAD] = "Assets/Images/Icons/abilities/ghostLoad.png",
        [HEMO_CYCLE] = "Assets/Images/Icons/abilities/hemocycle.png",
        [KINETIC_ARMOR] = "Assets/Images/Icons/abilities/kineticArmor.png",
        [LAST_STAND] = "Assets/Images/Icons/abilities/lastStand.png",
        [ONE_MORE] = "Assets/Images/Icons/abilities/oneMore.png",
        [OVER_PRESSURED] = "Assets/Images/Icons/abilities/overPressured.png",
        [SCAVENGER] = "Assets/Images/Icons/abilities/scavenger.png"
    };

    //This was copilot help, basically i just store the entire struct into an array of bool
    bool skillValues[TOTAL_SKILLS] = {
        player.state.skillState.armoredUp,
        player.state.skillState.ghostLoad,
        player.state.skillState.hemoCycle,
        player.state.skillState.kineticArmor,
        player.state.skillState.lastStand,
        player.state.skillState.oneMore,
        player.state.skillState.overPressured,
        player.state.skillState.scavenger

    };

    //The offset starts at -1 because when it offset++, it can start at 0, yes its 4:03 am and my brain is shit
    //Offset basically is just the integer that tells how many skills is actually active
    int Offset = -1;
    for(int i = 0; i < TOTAL_SKILLS; i++) {
        if(skillValues[i] == false)
        {
            //When the skill is false, we just skip it
            continue;
        }
        Offset++;
        //This goofy y and x position is to make it so it is centered but also after 4 in a row, it will make a new row
        int yPosition = 1;
        int xPosition = 0;
        if(Offset > 3) 
        {
            yPosition = 2; 
            xPosition = 160;
        }

        //This is the final position, the yposition is used to make a new row, the xposition is used so that the new row starts -160
        Vec2 position = {
            app.config.screen_width/2 - 100 + (Offset * 40) - xPosition,
            app.config.screen_height - 240 + (yPosition * 40)
        };
    
        //The rest is you alr know it. 
        int width = 40, height = 40;
        SDL_Texture* pixilFrame2Texture = IMG_LoadTexture(app.resources.renderer, AssetPath[i]);
        
        
        // Create destination rectangle
        SDL_Rect destRect = {
            (int)position.x,
            (int)position.y,
            (int)(width),
            (int)(height)
        };
        
        // Render the texture
        SDL_RenderCopy(app.resources.renderer, pixilFrame2Texture, NULL, &destRect);
    }       
}

void HUD_Render() {
    if (!game.hudToggled){
        Minimap_Render();
        HUD_RenderHealthBar();
        HUD_RenderAmmoBar();
        HUD_RenderCurrentGun();
        HUD_RenderCurrentLevel();
        HUD_RenderAmmoDisplay();
    }
    if(game.hudToggled)
    {
        HUD_RenderPixilFrame();
    }
    if (hasInteraction) {
        Interactable_RenderInteractableHUD();
    }
}