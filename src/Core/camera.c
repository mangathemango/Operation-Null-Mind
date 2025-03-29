/**
 * @file camera.c
 * @brief Game camera system
 *
 * Manages the game's camera view, handling player tracking,
 * coordinate transformations between screen and world space,
 * and viewport calculations.
 *
 * @author Mango
 * @date 2025-03-01
 */

#include <camera.h>
#include <app.h>
#include <input.h>

CameraSystem camera = {
    .position = {4200, 4200}
};

/**
 * [PostUpdate] Updates the camera position based on player position and mouse input
 */
void Camera_UpdatePosition() {
    float smoothTime = 3;
    // Linearly interpolate the position of the camera towards the player
    // This basically means the camera moves smoothly towards the position of the player
    
    Vec2 mouseToScreenCenter = Vec2_Subtract(
        Input->mouse.position,
        (Vec2) {
            app.config.screen_width / 2, 
            app.config.screen_height / 2
        }
    );
    Vec2 targetPosition = player.state.position;
    if (!player.state.movementLocked) {
        Vec2_Increment(&targetPosition, Vec2_Multiply(mouseToScreenCenter, 0.2f));
    }

    camera.position = Vec2_Lerp(
        camera.position, 
        targetPosition, 
        // Smooth time
        smoothTime * Time->deltaTimeSeconds
    );


}

/**
 * [Utility] Converts world coordinates to screen coordinates
 * 
 * @param worldPosition Position in world space
 * @return Vec2 Converted position in screen space
 */
Vec2 Camera_WorldVecToScreen(Vec2 worldPosition) {
    Vec2 offset = Vec2_Subtract(worldPosition, camera.position);
    Vec2 screenCenter = (Vec2) {app.config.screen_width / 2, app.config.screen_height / 2};
    return Vec2_Add(screenCenter, offset);
}

/**
 * [Utility] Converts screen coordinates to world coordinates
 * 
 * @param screenPosition Position in screen space
 * @return Vec2 Converted position in world space
 */
Vec2 Camera_ScreenVecToWorld(Vec2 screenPosition) {
    Vec2 screenCenter = (Vec2) {app.config.screen_width / 2, app.config.screen_height / 2};
    Vec2 offset = Vec2_Subtract(screenPosition, screenCenter);
    return Vec2_Add(camera.position, offset);
}

/**
 * [Utility] Converts a screen rectangle to world coordinates
 * 
 * @param screenRect Rectangle in screen space
 * @return SDL_Rect Converted rectangle in world space
 */
SDL_Rect Camera_ScreenRectToWorld(SDL_Rect screenRect) {
    Vec2 screenCenter = (Vec2) {app.config.screen_width / 2, app.config.screen_height / 2};
    Vec2 position, size;
    Vec2_FromRect(screenRect, &position, &size);
    Vec2 offset = Vec2_Subtract(position, screenCenter);
    Vec2 worldPos = Vec2_Add(camera.position, offset);

    return Vec2_ToRect(worldPos, size);
}

/**
 * [Utility] Gets the current view rectangle in world coordinates
 * 
 * @return SDL_Rect Rectangle representing the camera's view in world space
 */
SDL_Rect Camera_GetWorldViewRect() {
    return (SDL_Rect) {
        camera.position.x - app.config.screen_width / 2,
        camera.position.y - app.config.screen_height / 2,
        app.config.screen_width,
        app.config.screen_height
    };
}

/**
 * [Utility] Checks if a rectangle is visible on screen
 * 
 * @param rect Rectangle in world coordinates to check
 * @return bool True if the rectangle is at least partially visible, false otherwise
 */
bool Camera_WorldRectIsOnScreen(SDL_Rect rect) {
    SDL_Rect cameraRect = Camera_GetWorldViewRect();
    return SDL_HasIntersection(&rect, &cameraRect);
}

bool Camera_ScreenRectIsOnScreen(SDL_Rect rect) {
    return SDL_HasIntersection(
        &rect, 
        &(SDL_Rect) {
            0, 
            0, 
            app.config.screen_width, 
            app.config.screen_height
        }
    );
}