#include <settings.h>
#include <input.h>
#include <app.h>

void Settings_Start() {

}

void Settings_Update() {
    if (Input->mouse.leftButton.pressed) {
        app.state.currentScene = SCENE_MENU;
    }
}

void Settings_Render() {

}