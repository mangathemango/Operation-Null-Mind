#include <animation.h>
#include <stdlib.h>
#include <string.h>
#include <app.h>
#include <time_system.h>

Animation* Animation_Create(SDL_Texture* spritesheet, Vec2 frameSize, int frameCount) {
    Animation* animation = malloc(sizeof(Animation));
    if (!animation) return NULL;
    animation->spritesheet = spritesheet;
    animation->clips = NULL;
    animation->clipCount = 0;
    animation->frameSize = frameSize;
    animation->frameCount = frameCount;
    animation->currentClip = -1;
    animation->currentFrame = 0;
    animation->isPlaying = false;
    animation->direction = 1;
    return animation;
}

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

// Find clip index by name
static int Animation_FindClipIndex(Animation* animation, const char* clipName) {
    for (int i = 0; i < animation->clipCount; i++) {
        if (strcmp(animation->clips[i].name, clipName) == 0) {
            return i;
        }
    }
    return -1;
}

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

void Animation_Stop(Animation* animation) {
    animation->isPlaying = false;
    animation->currentFrame = 0;
    animation->timer = 0.0f;
}

void Animation_Pause(Animation* animation) {
    animation->isPlaying = false;
}

void Animation_Resume(Animation* animation) {
    animation->isPlaying = true;
}

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

void Animation_Render(Animation* animation, Vec2 destPosition, Vec2 destSize) {
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
        app.setup.renderer,
        animation->spritesheet,
        &srcRect,
        &dstRect,
        0,      // No rotation
        NULL,   // No rotation center (default)
        SDL_FLIP_NONE  // Flip horizontally/vertically if needed
    );
}