/**
 * @file animation.c
 * @brief Sprite animation system implementation
 *
 * Implements a flexible animation system that supports spritesheet-based
 * animations with multiple clips, variable frame rates, and playback controls.
 *
 * @author Mango
 * @date 2025-03-03
 */

//? Written by Mango on 03/03/2025

#include <animation.h>
#include <stdlib.h>
#include <string.h>
#include <app.h>
#include <time_system.h>

/**
 * @brief Creates a new animation from animation data
 *
 * This only works with spritesheets with constant frame size.
 * After creating an animation, calling Animation_AddClipFromGrid
 * can add additional animation clips.
 *
 * @param animData Pointer to the animation data configuration
 * @return Animation* Pointer to the new animation, or NULL if failed
 */
Animation* Animation_Create(AnimationData* animData) {
    if (!animData) return NULL;
    Animation* animation = malloc(sizeof(Animation));
    if (!animation) return NULL;

    animation->spritesheet = IMG_LoadTexture(app.resources.renderer, animData->spritesheetPath);
    if (!animation->spritesheet) {
        SDL_Log("Failed to load spritesheet: %s", animData->spritesheetPath);
        free(animation);
        return NULL;
    }
    animation->clips = NULL;
    animation->clipCount = 0;
    animation->frameSize = animData->frameSize;
    animation->frameCount = animData->frameCount;
    animation->currentClip = -1;
    animation->currentFrame = 0;
    animation->isPlaying = false;
    animation->direction = 1;

    // Set up clips
    for (int i = 0; animData->clips[i].name != NULL; i++) {
        Animation_AddClipFromGrid(animation, 
            animData->clips[i].name, 
            animData->clips[i].startFrameIndex, 
            animData->clips[i].endFrameIndex, 
            animData->clips[i].frameDuration, 
            animData->clips[i].looping);
    }

    if (animData->playOnStart) {
        Animation_Play(animation, animData->defaultClip);
    }
    return animation;
}

/**
 * @brief Updates the current animation frame
 *
 * This function should be called every frame to advance animations.
 * It handles transitions between frames, respecting frame durations
 * and looping settings.
 *
 * @param animation Pointer to the animation to update
 */
void Animation_Update(Animation* animation) {
    if (!animation->isPlaying || animation->currentClip < 0) {
        return;
    }
    
    AnimationClip* clip = &animation->clips[animation->currentClip];
    
    // Add time to timer
    animation->timer += Time->deltaTimeSeconds;
    
    // Check if it's time for next frame
    if (animation->timer >= clip->frameDuration) {
        animation->timer -= clip->frameDuration;
        
        // Move to next frame
        animation->currentFrame += animation->direction;
        
        // Handle end of animation
        if (animation->currentFrame >= clip->frameCount) {
            if (clip->looping) {
                animation->currentFrame = 0;
            } else {
                animation->currentFrame = clip->frameCount - 1;
                animation->isPlaying = false;
            }
        } else if (animation->currentFrame < 0) {
            if (clip->looping) {
                animation->currentFrame = clip->frameCount - 1;
            } else {
                animation->currentFrame = 0;
                animation->isPlaying = false;
            }
        }
    }
}

/**
 * @brief Destroys an animation and frees its resources
 *
 * @param animation Pointer to the animation to destroy
 */
void Animation_Destroy(Animation* animation) {
    // Free clip names and frame arrays
    for (int i = 0; i < animation->clipCount; i++) {
        free(animation->clips[i].name);
        free(animation->clips[i].frames);
    }
    
    // Free clips array
    free(animation->clips);
    
    // Free animation struct
    free(animation);
}

/**
 * @brief Adds an animation clip from a spritesheet grid
 *
 * Creates a new clip by extracting frames from the spritesheet
 * using a grid-based layout. Frame indices start from 0, reading
 * from left to right, then top to bottom.
 *
 * @param animation The animation to add the clip to
 * @param name Name of the clip (e.g., "idle", "walk")
 * @param startFrameIndex Index of the first frame in the clip
 * @param endFrameIndex Index of the last frame in the clip
 * @param frameDuration Time between frames in seconds
 * @param looping Whether the animation should loop
 * @return int 0 on success, 1 on failure
 */
int Animation_AddClipFromGrid(Animation* animation, const char* name,
                              int startFrameIndex, int endFrameIndex,
                              float frameDuration, bool looping) {

    int frameCount = endFrameIndex - startFrameIndex + 1;
    if (startFrameIndex < 0 || endFrameIndex > animation->frameCount) return 1;
    
    int spritesheetWidth, spritesheetHeight;
    SDL_QueryTexture(animation->spritesheet, NULL, NULL, &spritesheetWidth, &spritesheetHeight);
    
    AnimationFrame* frames = malloc(frameCount * sizeof(AnimationFrame));
    if (!frames) return 1;
    
    int frameIndex = 0;
    for (int y = 0; y < spritesheetHeight; y += animation->frameSize.y) {
        for (int x = 0; x < spritesheetWidth; x += animation->frameSize.x) {
            if (frameIndex < startFrameIndex) {
                frameIndex++;
                continue;
            }
            if (frameIndex > endFrameIndex) {
                break;
            }
            int currentIndex = frameIndex - startFrameIndex;
            frames[currentIndex].position = (Vec2) {x, y};
            frames[currentIndex].size = animation->frameSize;
            frameIndex++;
        }
    }

    // Expand clips array
    animation->clips = realloc(animation->clips, (animation->clipCount + 1) * sizeof(AnimationClip));
    
    // Get reference to new clip
    AnimationClip* clip = &animation->clips[animation->clipCount];
    
    // Copy name
    clip->name = strdup(name);
    
    // Allocate and copy frames
    clip->frames = malloc(frameCount * sizeof(AnimationFrame));
    memcpy(clip->frames, frames, frameCount * sizeof(AnimationFrame));
    free(frames);
    // Set other properties
    clip->frameCount = frameCount;
    clip->frameDuration = frameDuration;
    clip->looping = looping;
    
    animation->clipCount++;
    return 0;
}

/**
 * @brief Finds the index of an animation clip by name
 *
 * @param animation The animation to search in
 * @param clipName The name of the clip to find
 * @return int Index of the clip, or -1 if not found
 */
static int Animation_FindClipIndex(Animation* animation, const char* clipName) {
    for (int i = 0; i < animation->clipCount; i++) {
        if (strcmp(animation->clips[i].name, clipName) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Plays an animation clip by name
 *
 * If the target clip is already playing, this function does nothing.
 *
 * @param animation The animation to play
 * @param clipName The name of the clip to play
 */
void Animation_Play(Animation* animation, const char* clipName) {
    if (animation->currentClip >= 0 && animation->isPlaying) {
        if (strcmp(animation->clips[animation->currentClip].name, clipName) == 0) {
            return;
        }
    }
    int clipIndex = Animation_FindClipIndex(animation, clipName);
    if (clipIndex < 0) return;
    
    animation->currentClip = clipIndex;
    animation->currentFrame = 0;
    animation->timer = 0.0f;
    animation->isPlaying = true;
    animation->direction = 1;
}

/**
 * @brief Stops the current animation and resets it
 *
 * @param animation The animation to stop
 */
void Animation_Stop(Animation* animation) {
    animation->isPlaying = false;
    animation->currentFrame = 0;
    animation->timer = 0.0f;
}

/**
 * @brief Pauses the current animation
 *
 * @param animation The animation to pause
 */
void Animation_Pause(Animation* animation) {
    animation->isPlaying = false;
}

/**
 * @brief Resumes a paused animation
 *
 * @param animation The animation to resume
 */
void Animation_Resume(Animation* animation) {
    animation->isPlaying = true;
}

/**
 * @brief Renders the current frame of an animation
 *
 * @param animation The animation to render
 * @param destPosition Position where the animation should be drawn
 * @param destSize Size of the drawn animation
 * @param angle Rotation angle in degrees
 * @param rotationCenter Center point for rotation
 * @param flip Flip flags for rendering (horizontal/vertical)
 */
void Animation_Render(Animation* animation, Vec2 destPosition, Vec2 destSize,
                      float angle, SDL_Point* rotationCenter, SDL_RendererFlip flip) {
    // Make sure we have a valid clip
    if (animation->currentClip < 0 || animation->currentClip >= animation->clipCount) {
        return;
    }
    
    // Get current clip and frame
    AnimationClip* clip = &animation->clips[animation->currentClip];
    AnimationFrame* frame = &clip->frames[animation->currentFrame];
    
    // Create source rectangle (area in the spritesheet)
    SDL_Rect srcRect = {
        frame->position.x, 
        frame->position.y, 
        frame->size.x, 
        frame->size.y       
    };
    
    // Create destination rectangle (where to render on screen)
    SDL_Rect dstRect = {
        destPosition.x, 
        destPosition.y, 
        destSize.x,
        destSize.y
    };
    
    // Render the frame with the specified flip
    SDL_RenderCopyEx(
        app.resources.renderer,
        animation->spritesheet,
        &srcRect,
        &dstRect,
        angle,      // No rotation
        rotationCenter,   // No rotation center (default)
        flip  // Flip horizontally/vertically if needed
    );
}

bool Animation_ClipIsFinished(Animation* animation) {
    if (animation->currentClip < 0) return false;
    return animation->currentFrame == animation->clips[animation->currentClip].frameCount - 1;
}