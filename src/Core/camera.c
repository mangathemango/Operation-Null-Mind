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

Vec2 Camera_WorldToScreen(Vec2 worldPosition) {
    Vec2 offset = Vec2_Subtract(worldPosition, camera.position);
    Vec2 screenCenter = (Vec2) {app.config.screen_width / 2, app.config.screen_height / 2};
    return Vec2_Add(screenCenter, offset);
}

Vec2 Camera_ScreenToWorld(Vec2 screenPosition) {
    Vec2 screenCenter = (Vec2) {app.config.screen_width / 2, app.config.screen_height / 2};
    Vec2 offset = Vec2_Subtract(screenPosition, screenCenter);
    return Vec2_Add(camera.position, offset);
}