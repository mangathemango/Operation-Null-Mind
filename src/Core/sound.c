#include <sound.h>
#include <stdio.h>
#include <SDL_mixer.h>

// Initialize the sound resources structure
SoundResources soundResources = {
    .backgroundMusic = NULL,
    .soundEffects = {NULL}, //If you have more sound effects, increase the array size first. 
    .soundEffectCount = 0
};

bool Sound_System_Initialize() {
    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    
    return true;
}

bool Sound_Load_Resources() {
    // Load background music
    soundResources.backgroundMusic = Mix_LoadMUS("Assets/Audio/background.mp3");
    if (soundResources.backgroundMusic == NULL) {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    
    // Load sound effects
    soundResources.soundEffects[soundResources.soundEffectCount] = Mix_LoadWAV("Assets/Audio/swoosh.wav");
    if (soundResources.soundEffects[soundResources.soundEffectCount] == NULL) {
        printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    soundResources.soundEffectCount++;
    
    // Add more sound effects as needed
    
    return true;
}

void Sound_Play_Music(const char* path, int loops) {
    Mix_PlayMusic(soundResources.backgroundMusic, loops); //To do infinite loops, use -1
}

void Sound_Play_Effect(int index) {
    if (index >= 0 && index < soundResources.soundEffectCount) {
        Mix_PlayChannel(-1, soundResources.soundEffects[index], 0);
    }
}

void Sound_Stop_Music() {
    Mix_HaltMusic();
}

void Sound_System_Cleanup() {
    // Free music
    if (soundResources.backgroundMusic != NULL) {
        Mix_FreeMusic(soundResources.backgroundMusic);
        soundResources.backgroundMusic = NULL;
    }
    
    // Free sound effects
    for (int i = 0; i < soundResources.soundEffectCount; i++) {
        if (soundResources.soundEffects[i] != NULL) {
            Mix_FreeChunk(soundResources.soundEffects[i]);
            soundResources.soundEffects[i] = NULL;
        }
    }
    
    soundResources.soundEffectCount = 0;
    Mix_CloseAudio();
}