/**
 * @file sound.c
 * @brief Sound system implementation
 *
 * Manages the game's audio resources, including sound effects,
 * music playback, and volume controls.
 * 
 * @author Darren
 * @date 2025-03-07
 */

//? Written by Darren on 07/03/2025

#include <sound.h>
#include <stdio.h>
#include <SDL_mixer.h>


// Initialize the sound resources structure
SoundResources soundResources = {
    .backgroundMusic = NULL,
    .soundEffects = {NULL}, // Will be populated in Sound_Load_Resources()
    .soundPaths = {
        [SOUND_SWOOSH] = "Assets/Audio/swoosh.wav",                // SOUND_SWOOSH
        [SOUND_GUNSHOT] = "Assets/Audio/gunshot.wav",               // SOUND_GUNSHOT
        [SOUND_VINE_BOOM] = "Assets/Audio/VineBoom.wav",            // SOUND_VINE_BOOM
        [SOUND_BOOST_UP] = "Assets/Audio/boost up.wav",             // SOUND_BOOST_UP
        [SOUND_BUFFING] = "Assets/Audio/buffing.wav",               // SOUND_BUFFING
        [SOUND_CRATE_OPENING] = "Assets/Audio/crate opening.wav",   // SOUND_CRATE_OPENING
        [SOUND_DASH] = "Assets/Audio/dash.wav",                     // SOUND_DASH
        [SOUND_ELEVATOR_CLOSE] = "Assets/Audio/elevator close.wav", // SOUND_ELEVATOR_CLOSE
        [SOUND_ELEVATOR_OPEN] = "Assets/Audio/elevator open.wav",   // SOUND_ELEVATOR_OPEN
        [SOUND_ENEMY_HEALING] = "Assets/Audio/enemy healing.wav",   // SOUND_ENEMY_HEALING
        [SOUND_ENERGY_GUNSHOT] = "Assets/Audio/Energy Gunshot.wav",   // SOUND_ENERGY_GUNSHOT
        [SOUND_EXPLOSION] = "Assets/Audio/explosion.wav",           // SOUND_EXPLOSION
        [SOUND_GRENADE_LAUNCHER] = "Assets/Audio/grenade launcher.wav", // SOUND_GRENADE_LAUNCHER
        [SOUND_GUN_PICKUP] = "Assets/Audio/gun pickup.wav",         // SOUND_GUN_PICKUP
        [SOUND_HITMARKER] = "Assets/Audio/hitmarker.wav",           // SOUND_HITMARKER
        [SOUND_KAMIKAZE_BEEP] = "Assets/Audio/kamikaze beep.wav",   // SOUND_KAMIKAZE_BEEP
        [SOUND_LAST_STAND] = "Assets/Audio/Last Stand Used Up.wav",   // SOUND_LAST_STAND
        [SOUND_PARRY] = "Assets/Audio/parry.wav",                   // SOUND_PARRY
        [SOUND_PASSIVE_OBTAINED] = "Assets/Audio/passive obtained.wav", // SOUND_PASSIVE_OBTAINED
        [SOUND_PLAYER_HEALING] = "Assets/Audio/player healing.wav",   // SOUND_PLAYER_HEALING
        [SOUND_PLAYER_HURT] = "Assets/Audio/player hurt.wav",         // SOUND_PLAYER_HURT
        [SOUND_RECALL] = "Assets/Audio/recall.wav",                  // SOUND_RECALL
        [SOUND_ROCKET_LAUNCH] = "Assets/Audio/rocket launch.wav",     // SOUND_ROCKET_LAUNCH
        [SOUND_SENTRY_LASER] = "Assets/Audio/Sentry Laser Cannon.wav", // SOUND_SENTRY_LASER
        [SOUND_SPAWN_IN] = "Assets/Audio/spawn in.wav",              // SOUND_SPAWN_IN
        [SOUND_VANTAGE_LASER] = "Assets/Audio/vantage laser gunshot.wav" // SOUND_VANTAGE_LASER
    }
};

/*
*   [Start] Initialize the sound system
*   @return true if successful, false otherwise
*/
bool Sound_System_Initialize() {
    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    
    return true;
}

/*
*   [Start] Load sound resources
*   @return true if successful, false otherwise
*/
bool Sound_Load_Resources() {
    // Load sound effects
    // TODO: Maybe make this into a function?
    for(int i = 0; i < SOUND_COUNT;i++){
        soundResources.soundEffects[i] = Mix_LoadWAV(soundResources.soundPaths[i]);
        if (soundResources.soundEffects[i] == NULL) {
            printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
            return false;
        }
    }
    // Add more sound effects as needed
    
    return true;
}

/*
*   [Start/Utility] Play background music
    @param path - path to the music file
    @param loops - number of times to loop the music. -1 for infinite loops
*/
void Sound_Play_Music(const char* path, int loops) {
    soundResources.backgroundMusic = Mix_LoadMUS(path);
    Mix_PlayMusic(soundResources.backgroundMusic, loops); //To do infinite loops, use -1
}

/**
 * [Utility] Play sound effect
 * 
 * @param index Index of the sound effect to play
 * @todo [sound.c:95] Maybe implement a way to play sound effects by name?
 */
void Sound_Play_Effect(int index) {
    if (index >= 0 && index < SOUND_COUNT) {
        Mix_PlayChannel(-1, soundResources.soundEffects[index], 0);
    }
}

/**
 * [Utility] Stop background music
 */
void Sound_Stop_Music() {
    Mix_HaltMusic();
}

/**
 * [Quit] Clean up sound resources
 */
void Sound_System_Cleanup() {
    // Free music
    if (soundResources.backgroundMusic != NULL) {
        Mix_FreeMusic(soundResources.backgroundMusic);
        soundResources.backgroundMusic = NULL;
    }
    
    // Free sound effects
    for (int i = 0; i < SOUND_COUNT; i++) {
        if (soundResources.soundEffects[i] != NULL) {
            Mix_FreeChunk(soundResources.soundEffects[i]);
            soundResources.soundEffects[i] = NULL;
        }
    }
    
    Mix_CloseAudio();
}