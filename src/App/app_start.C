#include <app.h>
#include <player.h>
#include <initialize_SDL.h>
#include <random.h>
#include <particle_emitterpresets.h>
#include <sound.h>
/*
*   [Start] This function is called at the start of the program.
?   It initializes everything needed for the program to run. Like the window, renderer, and later, the game.
*/
int App_Start() {
    RandomInit();
    if (Initialize_SDL()) return 1;
    if (Player_Start()) return 1;
    Gun_Start();

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

    Sound_Play_Music("Assets/Audio/background.mp3", -1);
    

    return 0;
    
}
