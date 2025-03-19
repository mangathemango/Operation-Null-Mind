#include <camera.h>
#include <app.h>
#include <input.h>

CameraSystem camera = {
    .position = {0, 0}
};

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

    Vec2 targetPosition = Vec2_Add(
        player.state.position,
        Vec2_Multiply(mouseToScreenCenter, 0.2f)
    );

    camera.position = Vec2_Lerp(
        camera.position, 
        targetPosition, 
        // Smooth time
        smoothTime * Time->deltaTimeSeconds
    );


}

Vec2 Camera_WorldVecToScreen(Vec2 worldPosition) {
    Vec2 offset = Vec2_Subtract(worldPosition, camera.position);
    Vec2 screenCenter = (Vec2) {app.config.screen_width / 2, app.config.screen_height / 2};
    return Vec2_Add(screenCenter, offset);
}

Vec2 Camera_ScreenVecToWorld(Vec2 screenPosition) {
    Vec2 screenCenter = (Vec2) {app.config.screen_width / 2, app.config.screen_height / 2};
    Vec2 offset = Vec2_Subtract(screenPosition, screenCenter);
    return Vec2_Add(camera.position, offset);
}

SDL_Rect Camera_ScreenRectToWorld(SDL_Rect screenRect) {
    Vec2 screenCenter = (Vec2) {app.config.screen_width / 2, app.config.screen_height / 2};
    Vec2 position, size;
    Vec2_FromRect(screenRect, &position, &size);
    Vec2 offset = Vec2_Subtract(position, screenCenter);
    Vec2 worldPos = Vec2_Add(camera.position, offset);

    return Vec2_ToRect(worldPos, size);
}



// Add to camera.c
SDL_Rect Camera_GetViewRect() {
    return (SDL_Rect) {
        camera.position.x - app.config.screen_width / 2,
        camera.position.y - app.config.screen_height / 2,
        app.config.screen_width,
        app.config.screen_height
    };
}

bool Camera_RectIsOnScreen(SDL_Rect rect) {
    SDL_Rect cameraRect = Camera_GetViewRect();
    return SDL_HasIntersection(&rect, &cameraRect);
}