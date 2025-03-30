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


// Add to sound.c
MusicQueue musicQueue = {
    .front = 0,
    .rear = -1,
    .count = 0,
    .isPlaying = false,
    .loopQueue = false
};


// Initialize the sound resources structure
SoundResources soundResources = {
    .backgroundMusic = NULL,
    .soundEffects = {NULL}, // Will be populated in Sound_Load_Resources()
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
        [SOUND_VANTAGE_LASER] = "Assets/Audio/SoundEffect/vantage laser gunshot.wav" // SOUND_VANTAGE_LASER
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


/**
 * [Callback] Called when music finishes playing
 * Automatically plays next song in queue if available
 */
void Music_Finished_Callback() {
    if (musicQueue.count > 0) {
        // Remove the song we just finished
        musicQueue.front = (musicQueue.front + 1) % MAX_MUSIC_QUEUE_SIZE;
        musicQueue.count--;
        
        // Play next song if available
        if (musicQueue.count > 0) {
            Sound_Play_Music(musicQueue.paths[musicQueue.front], 0); // Play once
        } else if (musicQueue.loopQueue && musicQueue.rear >= 0) {
            // Loop back to the beginning if enabled
            musicQueue.front = 0;
            musicQueue.count = musicQueue.rear + 1;
            Sound_Play_Music(musicQueue.paths[musicQueue.front], 0);
        } else {
            musicQueue.isPlaying = false;
        }
    } else {
        musicQueue.isPlaying = false;
    }
}

/**
 * [Utility] Adds a music file to the queue
 * 
 * @param path Path to the music file
 * @return true if added successfully, false if queue is full
 */
bool Sound_Queue_Music(const char* path) {
    if (musicQueue.count >= MAX_MUSIC_QUEUE_SIZE) {
        printf("Music queue is full, cannot add more\n");
        return false;
    }
    
    // Allocate memory for the path and copy it
    int nextPosition = (musicQueue.rear + 1) % MAX_MUSIC_QUEUE_SIZE;
    musicQueue.paths[nextPosition] = strdup(path);
    musicQueue.rear = nextPosition;
    musicQueue.count++;
    
    // If this is the only song in the queue and we're not playing, start it
    if (musicQueue.count == 1 && !musicQueue.isPlaying) {
        musicQueue.isPlaying = true;
        Mix_HookMusicFinished(Music_Finished_Callback);
        Sound_Play_Music(musicQueue.paths[musicQueue.front], 0); // Play once
    }
    
    return true;
}

/**
 * [Utility] Skips to the next song in the queue
 * 
 * @return true if skipped successfully, false if queue is empty
 */
bool Sound_Skip_To_Next() {
    if (musicQueue.count <= 0) {
        return false;
    }
    
    // Stop current music
    Mix_HaltMusic();
    
    // Music_Finished_Callback will be called automatically
    // which will advance to the next song
    
    return true;
}

/**
 * [Utility] Sets whether the queue should loop
 * 
 * @param loop true to enable looping, false to disable
 */
void Sound_Set_Queue_Loop(bool loop) {
    musicQueue.loopQueue = loop;
}

/**
 * [Utility] Clears the music queue and stops playback
 */
void Sound_Clear_Queue() {
    // Stop current music
    Mix_HaltMusic();
    Mix_HookMusicFinished(NULL);
    
    // Free any allocated strings
    for (int i = 0; i < musicQueue.count; i++) {
        int index = (musicQueue.front + i) % MAX_MUSIC_QUEUE_SIZE;
        free(musicQueue.paths[index]);
    }
    
    // Reset queue state
    musicQueue.front = 0;
    musicQueue.rear = -1;
    musicQueue.count = 0;
    musicQueue.isPlaying = false;
}