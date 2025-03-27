/**
 * @file animation.h
 * @brief A simple animation system capable of loading a spritesheet with fixed sized frames
 *
 * The spritesheet you select should have all of its states on it, like running, walking etc.
 * @warning This system doesn't support loading animation clips from multiple files into one animation.
 *
 * @section animation_usage Usage
 * To load an animation, you need 3 steps:
 *
 * @subsection step1 Step 1: Create animation with an AnimationData struct
 * An example of an AnimationData struct can be found in src/Game/Player/player_data.c
 *
 * After that, you can call:
 * ```c
 * Animation* animation = Animation_Create(data);
 * ```
 *
 * @subsection step2 Step 2: Play the animation based on a certain state
 * ```c
 * Animation_Play(animation, "running");
 * ```
 *
 * @subsection step3 Step 3: Update and render the animation every frame
 * ```c
 * // Inside update loop
 * Animation_Update(animation);
 *
 * // Inside render loop
 * Animation_Render(
 *     animation,          // The animation
 *     (Vec2) {x, y},      // The position to render
 *     (Vec2) {w, h},      // The size to render
 *     angle,              // Rotation angle in degrees
 *     NULL,               // The rotation center, NULL for center
 *     SDL_FLIP_NONE       // Flip the sprite, SDL_FLIP_NONE for no flip
 * );
 * ```
 *
 * @author Mango
 * @date 2025-03-01
 */

#pragma once

#include <SDL.h>
#include <stdbool.h>
#include <vec2.h>

/**
 * @brief Represents a single frame in an animation.
 */
typedef struct {
    Vec2 position;  /**< Position of the frame in the spritesheet */
    Vec2 size;      /**< Size of the frame */
} AnimationFrame;

/**
 * @brief Represents an animation clip, which is a sequence of frames.
 */
typedef struct {
    char* name;             /**< Animation name (e.g., "idle", "walk") */
    AnimationFrame* frames; /**< Array of frames */
    int frameCount;         /**< Number of frames */
    float frameDuration;    /**< Time per frame in seconds */
    bool looping;           /**< Whether animation should loop */
} AnimationClip;

/**
 * @brief Data structure for defining an animation clip.
 */
typedef struct {
    char* name;           /**< Name of the animation clip */
    int startFrameIndex;  /**< Starting frame index in the spritesheet */
    int endFrameIndex;    /**< Ending frame index in the spritesheet */
    float frameDuration;  /**< Duration of each frame in seconds */
    bool looping;         /**< Whether the animation should loop */
} AnimationClipData;

/**
 * @brief The main animation structure.
 */
typedef struct {
    SDL_Texture* spritesheet;  /**< Spritesheet texture */
    AnimationClip* clips;      /**< Array of different animations */
    int clipCount;             /**< Number of animation clips */
    
    Vec2 frameSize;            /**< Size of each frame in the spritesheet */
    int frameCount;            /**< Total number of frames in the spritesheet */
    
    // Current animation state
    int currentClip;           /**< Currently active clip index */
    int currentFrame;          /**< Current frame within the clip */
    float timer;               /**< Time accumulator for frame changes */
    bool isPlaying;            /**< Whether animation is playing */
    int direction;             /**< 1 for forward, -1 for backward */
} Animation;

/**
 * @brief Configuration data for creating an animation.
 */
typedef struct {
    char* spritesheetPath;    /**< The path to the spriteSheet */
    Vec2 frameSize;           /**< The size of each frame in the sprite sheet */
    int frameCount;           /**< Number of frames inside the sprite sheet */
    AnimationClipData clips[5]; /**< Array of different animation clips */
    Vec2 spriteSize;          /**< The size of the rendered sprite */
    char* defaultClip;        /**< The default clip to play */
    bool playOnStart;         /**< Whether to play the animation on creation */
} AnimationData;

/**
 * @brief Creates a new animation from animation data.
 * @param data The animation data.
 * @return A pointer to the newly created animation.
 */
Animation* Animation_Create(AnimationData* data);

/**
 * @brief Destroys an animation and frees its memory.
 * @param animation The animation to destroy.
 */
void Animation_Destroy(Animation* animation);

/**
 * @brief Adds a new animation clip from a grid-based spritesheet.
 * @param animation The animation to add the clip to.
 * @param name The name of the clip.
 * @param startFrameIndex The index of the first frame.
 * @param endFrameIndex The index of the last frame.
 * @param frameDuration The duration of each frame in seconds.
 * @param looping Whether the animation should loop.
 * @return The index of the newly added clip.
 */
int Animation_AddClipFromGrid(Animation* animation, const char* name,
                                int startFrameIndex, int endFrameIndex,
                                float frameDuration, bool looping );

/**
 * @brief Plays an animation clip by name.
 * @param animation The animation to play.
 * @param clipName The name of the clip to play.
 */
void Animation_Play(Animation* animation, const char* clipName);

/**
 * @brief Stops the animation.
 * @param animation The animation to stop.
 */
void Animation_Stop(Animation* animation);

/**
 * @brief Pauses the animation.
 * @param animation The animation to pause.
 */
void Animation_Pause(Animation* animation);

/**
 * @brief Resumes the animation.
 * @param animation The animation to resume.
 */
void Animation_Resume(Animation* animation);

/**
 * @brief Updates the animation.
 * @param animation The animation to update.
 */
void Animation_Update(Animation* animation);

/**
 * @brief Renders the animation.
 * @param animation The animation to render.
 * @param destPosition The position to render the animation at.
 * @param destSize The size to render the animation at.
 * @param angle The angle to rotate the animation.
 * @param rotationCenter The center of rotation. NULL for center.
 * @param flip The flip mode for the sprite.
 */
void Animation_Render(
    Animation* animation, Vec2 destPosition, Vec2 destSize,
    float angle, SDL_Point* rotationCenter, SDL_RendererFlip flip
);

bool Animation_ClipIsFinished(Animation* animation);