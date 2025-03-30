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
    SOUND_SWOOSH = 0,             // Swoosh sound (Assets/Audio/SoundEffect/swoosh.wav)
    SOUND_GUNSHOT = 1,            // Gun firing sound (Assets/Audio/SoundEffect/gunshot.wav)
    SOUND_VINE_BOOM = 2,          // Vine boom sound (Assets/Audio/SoundEffect/VineBoom.wav)
    SOUND_BOOST_UP = 3,           // Boost sound (Assets/Audio/SoundEffect/boost up.wav)
    SOUND_BUFFING = 4,            // Buffing sound (Assets/Audio/SoundEffect/buffing.wav)
    SOUND_CRATE_OPENING = 5,      // Crate opening sound (Assets/Audio/SoundEffect/crate opening.wav)
    SOUND_DASH = 6,               // Dash movement sound (Assets/Audio/SoundEffect/dash.wav)
    SOUND_ELEVATOR_CLOSE = 7,     // Elevator closing sound (Assets/Audio/SoundEffect/elevator close.wav)
    SOUND_ELEVATOR_OPEN = 8,      // Elevator opening sound (Assets/Audio/SoundEffect/elevator open.wav)
    SOUND_ENEMY_HEALING = 9,      // Enemy healing sound (Assets/Audio/SoundEffect/enemy healing.wav)
    SOUND_ENERGY_GUNSHOT = 10,    // Energy weapon firing (Assets/Audio/SoundEffect/Energy Gunshot.wav)
    SOUND_EXPLOSION = 11,         // Explosion sound (Assets/Audio/SoundEffect/explosion.wav)
    SOUND_GRENADE_LAUNCHER = 12,  // Grenade launcher sound (Assets/Audio/SoundEffect/grenade launcher.wav)
    SOUND_GUN_PICKUP = 13,        // Gun pickup sound (Assets/Audio/SoundEffect/gun pickup.wav)
    SOUND_HITMARKER = 14,         // Hit confirmation sound (Assets/Audio/SoundEffect/hitmarker.wav)
    SOUND_KAMIKAZE_BEEP = 15,     // Kamikaze enemy beeping (Assets/Audio/SoundEffect/kamikaze beep.wav)
    SOUND_LAST_STAND = 16,        // Last Stand ability depletion (Assets/Audio/SoundEffect/Last Stand Used Up.wav)
    SOUND_PARRY = 17,             // Parry sound effect (Assets/Audio/SoundEffect/parry.wav)
    SOUND_PASSIVE_OBTAINED = 18,  // Passive ability acquired (Assets/Audio/SoundEffect/passive obtained.wav)
    SOUND_PLAYER_HEALING = 19,    // Player healing sound (Assets/Audio/SoundEffect/player healing.wav)
    SOUND_PLAYER_HURT = 20,       // Player damage sound (Assets/Audio/SoundEffect/player hurt.wav)
    SOUND_RECALL = 21,            // Recall ability sound (Assets/Audio/SoundEffect/recall.wav)
    SOUND_ROCKET_LAUNCH = 22,     // Rocket launcher sound (Assets/Audio/SoundEffect/rocket launch.wav)
    SOUND_SENTRY_LASER = 23,      // Sentry weapon firing (Assets/Audio/SoundEffect/Sentry Laser Cannon.wav)
    SOUND_SPAWN_IN = 24,          // Player/enemy spawn sound (Assets/Audio/SoundEffect/spawn in.wav)
    SOUND_VANTAGE_LASER = 25,     // Vantage laser firing (Assets/Audio/SoundEffect/vantage laser gunshot.wav)
    
    SOUND_COUNT                   // Total number of sound effects (automatically updated)
} SoundEffect;


// Sound resources structure
typedef struct {
    Mix_Music* backgroundMusic;
    Mix_Chunk* soundEffects[SOUND_COUNT]; // Array to store sound effects, add more if needed.
    char* soundPaths[SOUND_COUNT]; // Array to store sound paths, add more if needed.
} SoundResources;



typedef struct {
    char* paths[MAX_MUSIC_QUEUE_SIZE];
    int front;
    int rear;
    int count;
    bool isPlaying;
    bool loopQueue;
} MusicQueue;


extern SoundResources soundResources;

// Function declarations
bool Sound_System_Initialize();
bool Sound_Load_Resources();
void Sound_Play_Music(const char* path, int loops);
void Sound_Play_Effect(int index);
float Sound_Get_Music_Duration(const char* path);
void Sound_Stop_Music();
void Sound_System_Cleanup();

#endif