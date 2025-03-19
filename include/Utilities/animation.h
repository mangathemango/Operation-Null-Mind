/*
    @file animation.h
*   An simple animation system capable of loading a spritesheet with fixed sized frames
?   The spritesheet you select should have all of its states on it, like running, walking etc.
!   This system doesn't support loading animation clips from multiple files into one animation.
?   To load an animation, you need 3 steps.
?   
?   Step 1: Create animation with an AnimationData struct
?       An example of an AnimationData struct can be found in src/Game/Player/player_data.c
?   
?       After that, you can call:
?       Animation* animation = Animation_Create(data);
?   
?   Step 2: Play the animation based on a certain state:
?       Animation_Play(animation, "running");
?
?   Step 3: Update and render the animation every frame:
?       // Inside update loop
?       Animation_Update(animation);
?
?       // Inside render loop
?       Animation_Render(
?           animation,          // The animation
?           (Vec2) {x, y},      // The position to render
?           (Vec2) {w, h},      // The size to render
?           angle,              // Rotation angle in degrees
?           NULL,               // The rotation center, NULL for center
?           SDL_FLIP_NONE       // Flip the sprite, SDL_FLIP_NONE for no flip
?       );

?   Written by Mango on 01/03/2025
*/


#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>
#include <stdbool.h>
#include <vec2.h>


typedef struct {
    Vec2 position;
    Vec2 size;
} AnimationFrame;

typedef struct {
    char* name;             // Animation name (e.g., "idle", "walk")
    AnimationFrame* frames; // Array of frames
    int frameCount;         // Number of frames
    float frameDuration;    // Time per frame in seconds
    bool looping;           // Whether animation should loop
} AnimationClip;

typedef struct {
    char* name;
    int startFrameIndex;
    int endFrameIndex;
    float frameDuration;
    bool looping;
} AnimationClipData;
typedef struct {
    SDL_Texture* spritesheet;   // Spritesheet texture
    AnimationClip* clips;  // Array of different animations
    int clipCount;          // Number of animation clips
    
    Vec2 frameSize; 
    int frameCount;
    // Current animation state
    int currentClip;        // Currently active clip index
    int currentFrame;       // Current frame within the clip
    float timer;            // Time accumulator for frame changes
    bool isPlaying;         // Whether animation is playing
    int direction;          // 1 for forward, -1 for backward
} Animation;

typedef struct {
    char* spritesheetPath;  // The path to the spriteSheet
    Vec2 frameSize;         // The size of each frame in the sprite sheet
    int frameCount;         // Number of frames inside the sprite sheet
    AnimationClipData clips[5]; // Array of different animation clips
    Vec2 spriteSize;        // The size of the rendered sprite
    char* defaultClip;      // The default clip to play
    bool playOnStart;
} AnimationData;

// Create and destroy animations
Animation* Animation_Create(AnimationData* data);
void Animation_Destroy(Animation* animation);

// Add animation clips
int Animation_AddClipFromGrid(Animation* animation, const char* name,
                                int startFrameIndex, int endFrameIndex,
                                float frameDuration, bool looping );
// Animation control
void Animation_Play(Animation* animation, const char* clipName);
void Animation_Stop(Animation* animation);
void Animation_Pause(Animation* animation);
void Animation_Resume(Animation* animation);

// Update and render
void Animation_Update(Animation* animation);
void Animation_Render(Animation* animation, Vec2 destPosition, Vec2 destSize,
                        float angle, SDL_Point* rotationCenter, SDL_RendererFlip flip);

#endif
