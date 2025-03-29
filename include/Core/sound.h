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
    SOUND_SWOOSH = 0,             // Swoosh sound (Assets/Audio/swoosh.wav)
    SOUND_GUNSHOT = 1,            // Gun firing sound (Assets/Audio/gunshot.wav)
    SOUND_VINE_BOOM = 2,          // Vine boom sound (Assets/Audio/VineBoom.wav)
    SOUND_BOOST_UP = 3,           // Boost sound (Assets/Audio/boost up.wav)
    SOUND_BUFFING = 4,            // Buffing sound (Assets/Audio/buffing.wav)
    SOUND_CRATE_OPENING = 5,      // Crate opening sound (Assets/Audio/crate opening.wav)
    SOUND_DASH = 6,               // Dash movement sound (Assets/Audio/dash.wav)
    SOUND_ELEVATOR_CLOSE = 7,     // Elevator closing sound (Assets/Audio/elevator close.wav)
    SOUND_ELEVATOR_OPEN = 8,      // Elevator opening sound (Assets/Audio/elevator open.wav)
    SOUND_ENEMY_HEALING = 9,      // Enemy healing sound (Assets/Audio/enemy healing.wav)
    SOUND_ENERGY_GUNSHOT = 10,    // Energy weapon firing (Assets/Audio/Energy Gunshot.wav)
    SOUND_EXPLOSION = 11,         // Explosion sound (Assets/Audio/explosion.wav)
    SOUND_GRENADE_LAUNCHER = 12,  // Grenade launcher sound (Assets/Audio/grenade launcher.wav)
    SOUND_GUN_PICKUP = 13,        // Gun pickup sound (Assets/Audio/gun pickup.wav)
    SOUND_HITMARKER = 14,         // Hit confirmation sound (Assets/Audio/hitmarker.wav)
    SOUND_KAMIKAZE_BEEP = 15,     // Kamikaze enemy beeping (Assets/Audio/kamikaze beep.wav)
    SOUND_LAST_STAND = 16,        // Last Stand ability depletion (Assets/Audio/Last Stand Used Up.wav)
    SOUND_PARRY = 17,             // Parry sound effect (Assets/Audio/parry.wav)
    SOUND_PASSIVE_OBTAINED = 18,  // Passive ability acquired (Assets/Audio/passive obtained.wav)
    SOUND_PLAYER_HEALING = 19,    // Player healing sound (Assets/Audio/player healing.wav)
    SOUND_PLAYER_HURT = 20,       // Player damage sound (Assets/Audio/player hurt.wav)
    SOUND_RECALL = 21,            // Recall ability sound (Assets/Audio/recall.wav)
    SOUND_ROCKET_LAUNCH = 22,     // Rocket launcher sound (Assets/Audio/rocket launch.wav)
    SOUND_SENTRY_LASER = 23,      // Sentry weapon firing (Assets/Audio/Sentry Laser Cannon.wav)
    SOUND_SPAWN_IN = 24,          // Player/enemy spawn sound (Assets/Audio/spawn in.wav)
    SOUND_VANTAGE_LASER = 25,     // Vantage laser firing (Assets/Audio/vantage laser gunshot.wav)
    
    SOUND_COUNT                   // Total number of sound effects (automatically updated)
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