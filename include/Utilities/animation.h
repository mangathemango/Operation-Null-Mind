/*
    @file animation.h
*   An simple animation system capable of loading a spritesheet with fixed sized frames
?   The spritesheet you select should have all of its states on it, like running, walking etc.
!   This system doesn't support loading animation clips from multiple files into one animation.
?   To load an animation, you need 4 steps.
?   
!   This tutorial is deprecated and will be updated soon.
?   Step 1: Create animation with frame size and frame number
?       *Animation animation = Animation_Create(animationTexture, (Vec2) {x, y}, n);
?   
?   Step 2: Select frames from the spritesheet to make into a clip.
?   Note: Index counts from 0, and goes from left to right, THEN up to down
?   For example: If your running animation is from frames with index 5 to 10, you can run
?       Animation_AddClipFromGrid(animation, "running", 5, 10, 0.4f, true); 
?   
?   Step 3: Play the animation:
?       Animation_Play(animation, "running");
?
?   Step 4: Update and render the animation every frame:
?       Animation_Update(animation);
?       Animation_Render(animation, 
?                       (Vec2) {x, y}, 
?                       (Vec2) {w, h}, 
?                       angle, 
?                       NULL, 
?                       SDL_FLIP_NONE);

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
