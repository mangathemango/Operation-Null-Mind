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


#define MAX_MUSIC_QUEUE_SIZE 20

typedef enum {
    SOUND_SWOOSH,             // Swoosh sound (Assets/Audio/SoundEffect/swoosh.wav)
    SOUND_GUNSHOT,            // Gun firing sound (Assets/Audio/SoundEffect/gunshot.wav)
    SOUND_VINE_BOOM,          // Vine boom sound (Assets/Audio/SoundEffect/VineBoom.wav)
    SOUND_BOOST_UP,           // Boost sound (Assets/Audio/SoundEffect/boost up.wav)
    SOUND_BUFFING,            // Buffing sound (Assets/Audio/SoundEffect/buffing.wav)
    SOUND_CRATE_OPENING,      // Crate opening sound (Assets/Audio/SoundEffect/crate opening.wav)
    SOUND_DASH,               // Dash movement sound (Assets/Audio/SoundEffect/dash.wav)
    SOUND_ELEVATOR_CLOSE,     // Elevator closing sound (Assets/Audio/SoundEffect/elevator close.wav)
    SOUND_ELEVATOR_OPEN,      // Elevator opening sound (Assets/Audio/SoundEffect/elevator open.wav)
    SOUND_ENEMY_HEALING,      // Enemy healing sound (Assets/Audio/SoundEffect/enemy healing.wav)
    SOUND_ENERGY_GUNSHOT,    // Energy weapon firing (Assets/Audio/SoundEffect/Energy Gunshot.wav)
    SOUND_EXPLOSION,         // Explosion sound (Assets/Audio/SoundEffect/explosion.wav)
    SOUND_GRENADE_LAUNCHER,  // Grenade launcher sound (Assets/Audio/SoundEffect/grenade launcher.wav)
    SOUND_GUN_PICKUP,        // Gun pickup sound (Assets/Audio/SoundEffect/gun pickup.wav)
    SOUND_HITMARKER,         // Hit confirmation sound (Assets/Audio/SoundEffect/hitmarker.wav)
    SOUND_KAMIKAZE_BEEP,     // Kamikaze enemy beeping (Assets/Audio/SoundEffect/kamikaze beep.wav)
    SOUND_LAST_STAND,        // Last Stand ability depletion (Assets/Audio/SoundEffect/Last Stand Used Up.wav)
    SOUND_PARRY,             // Parry sound effect (Assets/Audio/SoundEffect/parry.wav)
    SOUND_PASSIVE_OBTAINED,  // Passive ability acquired (Assets/Audio/SoundEffect/passive obtained.wav)
    SOUND_PLAYER_HEALING,    // Player healing sound (Assets/Audio/SoundEffect/player healing.wav)
    SOUND_PLAYER_HURT,       // Player damage sound (Assets/Audio/SoundEffect/player hurt.wav)
    SOUND_RECALL,            // Recall ability sound (Assets/Audio/SoundEffect/recall.wav)
    SOUND_ROCKET_LAUNCH,     // Rocket launcher sound (Assets/Audio/SoundEffect/rocket launch.wav)
    SOUND_SENTRY_LASER,      // Sentry weapon firing (Assets/Audio/SoundEffect/Sentry Laser Cannon.wav)
    SOUND_SPAWN_IN,          // Player/enemy spawn sound (Assets/Audio/SoundEffect/spawn in.wav)
    SOUND_VANTAGE_LASER,     // Vantage laser firing (Assets/Audio/SoundEffect/vantage laser gunshot.wav)
    SOUND_BOOST_DOWN,        // Boost down sound (Assets/Audio/SoundEffect/boost down.wav)
    SOUND_HOVER,             // Hover sound (Assets/Audio/SoundEffect/hover.wav)

    SOUND_COUNT                   // Total number of sound effects (automatically updated)
} SoundEffect;


typedef struct {
    char* currentSongPath; // Path to the currently playing song
    char* nextSongPath;    // Path to the next song (NULL if none queued)
    bool hasNextSong;      // Flag to indicate if there's a next song
} SimpleQueue;

// Sound resources structure
typedef struct {
    Mix_Music* backgroundMusic;
    Mix_Music* nextMusic; // Pointer to the next music to be played
    Mix_Chunk* soundEffects[SOUND_COUNT]; // Array to store sound effects, add more if needed.
    char* soundPaths[SOUND_COUNT]; // Array to store sound paths, add more if needed.
    SimpleQueue musicQueue; // Queue for music playback
} SoundResources;


extern SoundResources soundResources;

// Function declarations
bool Sound_System_Initialize();
bool Sound_Load_Resources();
void Sound_Play_Music(const char* path, int loops);
void Sound_Play_Effect(int index);
float Sound_Get_Music_Duration(const char* path);
void Sound_Stop_Music();
void Sound_System_Cleanup();
bool Sound_Queue_Next_Song(const char* path);
void Sound_Clear_Queue();
void Music_Finished_Callback();
void Sound_Set_Max_Channels(int numChannels);

#endif