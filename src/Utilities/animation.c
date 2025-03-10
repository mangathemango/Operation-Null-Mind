//? Written by Mango on 03/03/2025

#include <animation.h>
#include <stdlib.h>
#include <string.h>
#include <app.h>
#include <time_system.h>

/*
*   [Start] Creates an animation from a spritesheet.
?   Can handle spritesheets with multiple rows and columns.
?   After creating an animation, call Animation_AddClipFromGrid to add animation clips
!   This only works with spritesheets with constant frame size

    @param spritesheet A pointer to the spritesheet texture
    @param How big each frame is in pixels.
    @param How many frames there are in the spritesheet. Don't count the blank frames btw.

*/
Animation* Animation_Create(AnimationData* animData) {
    Animation* animation = malloc(sizeof(Animation));
    if (!animation) return NULL;

    animation->spritesheet = IMG_LoadTexture(app.resources.renderer, animData->spritesheetPath);
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

/*
*   [PostUpdate] Updates the current animation.

?   This function should be called every frame inside App_PostUpdate();
    @param animation A pointer to the animation
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

/*
*   [Utility] Destroys an animation

    @param animation A pointer to the animation
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

/*
*   [Utility] Add an animation clip from an animation's spritesheet.

?   Note: Index numbering starts from 0, and goes from left to right, then up to down.
    @param animation The pointer to the animation
    @param name The name of the clip, for example "idle", "walk", etc.
    @param startFrameIndex The index of the beginning frame of the clip.
    @param endFrameIndex The index of the last frame of the clip.
    @param frameDuration The amount of time between frames.
    @param looping Whether the animation is looped.
    @returns 0 if successful, 1 if an error occured.
*/
int Animation_AddClipFromGrid(Animation* animation, const char* name,
                                        int startFrameIndex, int endFrameIndex,
                                        float frameDuration, bool looping ) {

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

/*
*   [Utility] Finds the animation clip with its name

    @param animation A pointer to the animation
    @param clipName The name of the clip
    @returns The index of the animationClip
*/
static int Animation_FindClipIndex(Animation* animation, const char* clipName) {
    for (int i = 0; i < animation->clipCount; i++) {
        SDL_Log("Looking at clip name: %s", animation->clips[i].name);
        if (strcmp(animation->clips[i].name, clipName) == 0) {
            return i;
        }
    }
    return -1;
}

/*
*   [Utility] Plays an animation clip.

?   If the target clip is currently playing, this function does nothing.

    @param animation A pointer to the animation
    @param clipName The name of the animation clip. For example "idle", "walk", etc.
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

/*
*   [Utility] Stops the current animation clip
    @param animation A pointer to the animation
*/
void Animation_Stop(Animation* animation) {
    animation->isPlaying = false;
    animation->currentFrame = 0;
    animation->timer = 0.0f;
}

/*
*   [Utility] Pause the current animation clip
    @param animation A pointer to the animation
*/
void Animation_Pause(Animation* animation) {
    animation->isPlaying = false;
}

/*
*   [Utility] Resume the current animation clip
    @param animation A pointer to the animation
*/
void Animation_Resume(Animation* animation) {
    animation->isPlaying = true;
}


/*
*   [Render] Renders an animation

    @param animation A pointer to the animation
    @param destPosition The position to draw
    @param destSize The size of the drawn image
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