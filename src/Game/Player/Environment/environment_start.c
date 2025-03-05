#include <environment.h>
#include <app.h>

void Environment_Start() {
    // This is where the environment will be initialized.
     Environment_AddWall(
         (Wall) {
            .wallSize = {app.config.screen_width - 20, 10, 10, app.config.screen_height},
            .hitbox = {0, 0, 10, app.config.screen_height},
            .texture = NULL
        }
    );
} 