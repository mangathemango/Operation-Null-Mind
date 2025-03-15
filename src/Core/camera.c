#include <camera.h>
#include <app.h>

CameraSystem camera = {
    .position = {0, 0}
};

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