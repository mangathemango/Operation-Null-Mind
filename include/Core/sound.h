/**
 * @file sound.h
 * @brief Manages audio playback for music and sound effects.
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

typedef enum {
    SOUND_SWOOSH = 0,     //** Swoosh sound (Assets/Audio/swoosh.wav)*/
    SOUND_GUNSHOT = 1,    //** Gun firing sound (Assets/Audio/gunshot.wav)*/
    SOUND_VINE_BOOM = 2,  //** Vine whip sound (Assets/Audio/VineWhip.wav) */
    
    SOUND_COUNT           //** Total number of sound effects (automatically updated) */
} SoundEffect;


// Sound resources structure
typedef struct {
    Mix_Music* backgroundMusic;
    Mix_Chunk* soundEffects[SOUND_COUNT]; // Array to store sound effects, add more if needed.
    char* soundPaths[SOUND_COUNT]; // Array to store sound paths, add more if needed.
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