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
#include <stdlib.h>  
#include <string.h>
#include <SDL.h> 
#include <settings.h>

/**
 * @brief Sets the maximum number of sound effect channels.
 *
 * @param numChannels The number of channels to allocate.
 */
void Sound_Set_Max_Channels(int numChannels) {
    Mix_AllocateChannels(numChannels);
}

// Initialize the sound resources structure
SoundResources soundResources = {
    .backgroundMusic = NULL,
    .soundEffects = {NULL}, // Will be populated in Sound_Load_Resources()
    .musicQueue.nextSongPath = "Assets/Audio/SoundEffect/explosion.wav",
    .soundPaths = {
        [SOUND_SWOOSH] = "Assets/Audio/SoundEffect/swoosh.wav",                // SOUND_SWOOSH
        [SOUND_GUNSHOT] = "Assets/Audio/SoundEffect/gunshot.wav",               // SOUND_GUNSHOT
        [SOUND_VINE_BOOM] = "Assets/Audio/SoundEffect/VineBoom.wav",            // SOUND_VINE_BOOM
        [SOUND_BOOST_UP] = "Assets/Audio/SoundEffect/boost up.wav",             // SOUND_BOOST_UP
        [SOUND_BUFFING] = "Assets/Audio/SoundEffect/buffing.wav",               // SOUND_BUFFING
        [SOUND_CRATE_OPENING] = "Assets/Audio/SoundEffect/crate opening.wav",   // SOUND_CRATE_OPENING
        [SOUND_DASH] = "Assets/Audio/SoundEffect/dash.wav",                     // SOUND_DASH
        [SOUND_ELEVATOR_CLOSE] = "Assets/Audio/SoundEffect/elevator close.wav", // SOUND_ELEVATOR_CLOSE
        [SOUND_ELEVATOR_OPEN] = "Assets/Audio/SoundEffect/elevator open.wav",   // SOUND_ELEVATOR_OPEN
        [SOUND_ENEMY_HEALING] = "Assets/Audio/SoundEffect/enemy healing.wav",   // SOUND_ENEMY_HEALING
        [SOUND_ENERGY_GUNSHOT] = "Assets/Audio/SoundEffect/Energy Gunshot.wav",   // SOUND_ENERGY_GUNSHOT
        [SOUND_EXPLOSION] = "Assets/Audio/SoundEffect/explosion.wav",           // SOUND_EXPLOSION
        [SOUND_GRENADE_LAUNCHER] = "Assets/Audio/SoundEffect/grenade launcher.wav", // SOUND_GRENADE_LAUNCHER
        [SOUND_GUN_PICKUP] = "Assets/Audio/SoundEffect/gun pickup.wav",         // SOUND_GUN_PICKUP
        [SOUND_HITMARKER] = "Assets/Audio/SoundEffect/hitmarker.wav",           // SOUND_HITMARKER
        [SOUND_KAMIKAZE_BEEP] = "Assets/Audio/SoundEffect/kamikaze beep.wav",   // SOUND_KAMIKAZE_BEEP
        [SOUND_LAST_STAND] = "Assets/Audio/SoundEffect/Last Stand Used Up.wav",   // SOUND_LAST_STAND
        [SOUND_PARRY] = "Assets/Audio/SoundEffect/parry.wav",                   // SOUND_PARRY
        [SOUND_PASSIVE_OBTAINED] = "Assets/Audio/SoundEffect/passive obtained.wav", // SOUND_PASSIVE_OBTAINED
        [SOUND_PLAYER_HEALING] = "Assets/Audio/SoundEffect/player healing.wav",   // SOUND_PLAYER_HEALING
        [SOUND_PLAYER_HURT] = "Assets/Audio/SoundEffect/player hurt.wav",         // SOUND_PLAYER_HURT
        [SOUND_RECALL] = "Assets/Audio/SoundEffect/recall.wav",                  // SOUND_RECALL
        [SOUND_ROCKET_LAUNCH] = "Assets/Audio/SoundEffect/rocket launch.wav",     // SOUND_ROCKET_LAUNCH
        [SOUND_SENTRY_LASER] = "Assets/Audio/SoundEffect/Sentry Laser Cannon.wav", // SOUND_SENTRY_LASER
        [SOUND_SPAWN_IN] = "Assets/Audio/SoundEffect/spawn in.wav",              // SOUND_SPAWN_IN
        [SOUND_VANTAGE_LASER] = "Assets/Audio/SoundEffect/vantage laser gunshot.wav", // SOUND_VANTAGE_LASER
        [SOUND_BOOST_DOWN] = "Assets/Audio/SoundEffect/boost down.wav",     // SOUND_BOOST_DOWN   
        [SOUND_HOVER] = "Assets/Audio/SoundEffect/hover.wav", // SOUND_HOVER       
        [SOUND_ARMOR_PISTOL] = "Assets/Audio/SoundEffect/Armor Pistol.wav", // SOUND_ARMOR_PISTOL
        [SOUND_ASSAULT_RIFLE] = "Assets/Audio/SoundEffect/Assault Rifle.wav", // SOUND_ASSAULT_RIFLE
        [SOUND_AUTO_SHOTGUN] = "Assets/Audio/SoundEffect/Auto Shotgun.wav", // SOUND_AUTO_SHOTGUN
        [SOUND_BATTLE_RIFLE] = "Assets/Audio/SoundEffect/Battle Rifle.wav", // SOUND_BATTLE_RIFLE
        [SOUND_BULLPUP_RIFLE] = "Assets/Audio/SoundEffect/Bullpup Rifle.wav", // SOUND_BULLPUP_RIFLE
        [SOUND_BURST_RIFLE] = "Assets/Audio/SoundEffect/Burst Rifle.wav", // SOUND_BURST_RIFLE
        [SOUND_PDW] = "Assets/Audio/SoundEffect/PDW.wav", // SOUND_PDW
        [SOUND_PISTOL] = "Assets/Audio/SoundEffect/Pistol.wav", // SOUND_PISTOL
        [SOUND_RAPID_SMG] = "Assets/Audio/SoundEffect/Rapid SMG.wav", // SOUND_RAPID_SMG
        [SOUND_REVOLVER] = "Assets/Audio/SoundEffect/Revolver.wav", // SOUND_REVOLVER
        [SOUND_SELECT] = "Assets/Audio/SoundEffect/select.wav", // SOUND_SELECT
        [SOUND_SHOTGUN] = "Assets/Audio/SoundEffect/Shotgun.wav", // SOUND_SHOTGUN
        [SOUND_SMG] = "Assets/Audio/SoundEffect/SMG.wav", // SOUND_SMG
        [SOUND_GUN_JAM] = "Assets/Audio/SoundEffect/gun jamming.wav" // SOUND_GUN_JAM
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
    Sound_Set_Max_Channels(32); // Set the maximum number of sound effect channels
    
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
// void Sound_Play_Music(const char* path, int loops) {
//     soundResources.backgroundMusic = Mix_LoadMUS(path);
//     Mix_PlayMusic(soundResources.backgroundMusic, loops); //To do infinite loops, use -1
// }

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


float Sound_Get_Music_Duration(const char* path) {
    Mix_Music* music = Mix_LoadMUS(path);
    if (!music) {
        printf("Failed to load music: %s\n", Mix_GetError());
        return -1.0f;
    }
    
    double duration = Mix_MusicDuration(music);
    Mix_FreeMusic(music);
    return (float)duration;
};

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


// Add to sound.c
SimpleQueue musicQueue = {
    .nextSongPath = NULL,
    .hasNextSong = false
};

/**
 * [Callback] Called when music finishes playing
 * Plays the next queued song if available
 */
void Music_Finished_Callback() {
    if (!musicQueue.hasNextSong) {
        SDL_Log("No next song queued.");
        return;
    }

    Sound_Play_Music(musicQueue.nextSongPath, 0); // Play once
        
    // Clear the queue
    free(musicQueue.nextSongPath);
    musicQueue.nextSongPath = NULL;
    musicQueue.hasNextSong = false;
}

/**
 * [Utility] Queue a single song to play next
 * @param path Path to the music file to play next
 * @return true if queued successfully, false if failed
 */
bool Sound_Queue_Next_Song(const char* path) {
    // If there's already a song queued, replace it
    if (musicQueue.nextSongPath != NULL) {
        free(musicQueue.nextSongPath);
    }
    
    // Queue the new song
    musicQueue.nextSongPath = strdup(path);
    musicQueue.hasNextSong = true;
    
    // Enable the callback to handle transition
    Mix_HookMusicFinished(Music_Finished_Callback);
    
    return true;
}

/**
 * [Utility] Clear the queued song
 */
void Sound_Clear_Queue() {
    if (musicQueue.nextSongPath != NULL) {
        free(musicQueue.nextSongPath);
        musicQueue.nextSongPath = NULL;
    }
    
    musicQueue.hasNextSong = false;
    Mix_HookMusicFinished(NULL); // Disable the callback
}

/**
 * [Update] Update Sound_Play_Music to free previous music
 */
void Sound_Play_Music(const char* path, int loops) {
    // Free previous music if it exists
    if (soundResources.backgroundMusic != NULL) {
        Mix_FreeMusic(soundResources.backgroundMusic);
        soundResources.backgroundMusic = NULL;
    }
    
    // Load and play new music
    soundResources.backgroundMusic = Mix_LoadMUS(path);
    if (soundResources.backgroundMusic == NULL) {
        printf("Failed to load music: %s\n", Mix_GetError());
        return;
    }
    
    Mix_PlayMusic(soundResources.backgroundMusic, loops);
}

void Sound_UpdateVolume() {
    float musicVolume = Settings_GetMusicVolume() * Settings_GetMasterVolume();
    float soundVolume = Settings_GetSoundVolume() * Settings_GetMasterVolume();
    Mix_VolumeMusic((int)(MIX_MAX_VOLUME * musicVolume));
    Mix_Volume(-1, (int)(MIX_MAX_VOLUME * soundVolume)); // Set volume for all channels
}