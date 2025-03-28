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
    .soundEffects = {NULL}, //If you have more sound effects, increase the array size first. 
    .soundPaths = {
        "Assets/Audio/swoosh.wav",
        "Assets/Audio/gunshot.wav",
        "Assets/Audio/VineBoom.wav"
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