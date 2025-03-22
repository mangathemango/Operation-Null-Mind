#include <app.h>
#include <player.h>
#include <initialize_SDL.h>
#include <random.h>
#include <particle_emitterpresets.h>
#include <sound.h>
#include <enemy_types.h>
#include <bullet.h>

/*
*   [Start] This function is called at the start of the program.
?   It initializes everything needed for the program to run. Like the window, renderer, and later, the game.

?   Updated by Mango on 08/03/2025
*/
int App_Start() {
    RandomInit();
    Collider_Start();
    if (Initialize_SDL()) return 1;
    if (Player_Start()) return 1;
    Gun_Start();
    Bullet_Start();
    Map_Start();
    Enemy_Init();
    Minimap_Start();
    // Initialize sound system
    if (!Sound_System_Initialize()) {
        SDL_Log("Failed to initialize sound system!");
        return 1;
    }

    // Load sound resources
    if (!Sound_Load_Resources()) {
        SDL_Log("Failed to load sound resources!\n");
        return 1;
    }

    Sound_System_Initialize();
    Menu_PrepareTextures();
    Pause_Start();
    return 0;
    
}
