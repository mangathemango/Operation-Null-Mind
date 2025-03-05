#include <player.h>
#include <app.h>

int Player_AnimationInit() {
    // Load spin animation
    SDL_Texture* animationTexture = IMG_LoadTexture(app.setup.renderer, "Assets/Images/511212 sprite sheet.png");

    // Create animation object
    player.config.animation = Animation_Create(animationTexture, (Vec2) {481, 489}, 28);
    if (!player.config.animation) {
        SDL_Log("Failed to create animation");
        SDL_DestroyTexture(animationTexture);
        return 1;
    }

    Animation_AddClipFromGrid(player.config.animation, "idle", 0, 0, 0.4f, true);
    Animation_AddClipFromGrid(player.config.animation, "spin", 1, 27, 0.05f, true);

    Animation_Play(player.config.animation, "idle");
    return 0;
}

int Player_AnimationUpdate() {
    if (player.state.moving)    Animation_Play(player.config.animation, "spin");
    else                        Animation_Play(player.config.animation, "idle");
    
    Animation_Update(player.config.animation);
    return 0;
}