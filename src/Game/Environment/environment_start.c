 #include <environment.h>
 #include <app.h>
 #include <SDL_image.h>

    // Define the environment

 int Environment_Start() {
    // Load the brick texture
    SDL_Texture* brickTexture = IMG_LoadTexture(app.resources.renderer, "Assets/Images/wall.png");
    if (!brickTexture) {
        SDL_Log("Failed to load brick texture: %s", SDL_GetError());
        return 0; // Initialization failed
    }

    // Add the wall to the environment
    Environment_AddWall((Wall) {
        .wallSize = {100, 100, 50, 20}, // Position (100, 100), width 200, height 50
        .collider =   {
            .active = true,
            .collidesWith = COLLISION_LAYER_NONE,
            .layer = COLLISION_LAYER_ENVIRONMENT,
            .hitbox = {100, 100, 50, 20},
        }, // Use the same size for the hitbox
        .texture = brickTexture
    });

    

    return 0; // Initialization successful
}

 

