/**
 * @file sound.h
 * @brief This file contains the sound system and its functions.
 * @details The sound system is used to play music and sound effects.
 *          It uses SDL_mixer to play the music and sound effects.
 *
 * @author Darren
 * @date 2025-07-03
 */

#ifndef sound
#define sound

#include <SDL_mixer.h>
#include <stdbool.h>

// Sound resources structure
typedef struct {
    Mix_Music* backgroundMusic;
    Mix_Chunk* soundEffects[10]; // Array to store sound effects, add more if needed.
    int soundEffectCount;
} SoundResources;

extern SoundResources soundResources;

// Function declarations
bool Sound_System_Initialize();
bool Sound_Load_Resources();
void Sound_Play_Music(const char* path, int loops);
void Sound_Play_Effect(int index);
void Sound_Stop_Music();
void Sound_System_Cleanup();

#endif