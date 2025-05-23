/**
 * @file app_start.C
 * @brief Application initialization
 *
 * Handles the initialization of all game systems during
 * program startup, including graphics, input, sound, and game state.
 *
 * @author Mango
 * @date 2025-03-08
 */

#include <app.h>
#include <player.h>
#include <initialize_SDL.h>
#include <random.h>
#include <particle_emitterpresets.h>
#include <sound.h>
#include <enemy_types.h>
#include <bullet.h>
#include <controls.h>
#include <win.h> // Added for Win_Start function
#include <settings.h>
#include <input.h>

/*
*   [Start] This function is called at the start of the program.
?   It initializes everything needed for the program to run. Like the window, renderer, and later, the game.

?   Updated by Mango on 08/03/2025
*/
int App_Start() {
    RandomInit();
    Collider_Start();
    // Initialize settings and input
    Input_Init();
    InitializeSettings();
    
    // Load settings and input bindings from the same file
    Settings_Load();  // This now loads both settings and input bindings
    
    if (Initialize_SDL()) return 1;
    Gun_Start();
    Bullet_Start();
    Interactable_Start();
    Map_Start();
    Enemy_Init();
    Minimap_Start();
    if (Player_Start()) return 1;
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
    Settings_Start();
    Sound_UpdateVolume();
    Menu_PrepareTextures();
    Pause_Start();
    Death_Start();
    Win_Start(); // Initialize the win screen
    Log_Start();
    HUD_Start();
    Game_Start();
    LevelTransition_Start();
    Mission_Start();
    Controls_Start();
    app.resources.cursorTexture = IMG_LoadTexture(app.resources.renderer, "Assets/Images/crosshair.png");
    return 0;
}
