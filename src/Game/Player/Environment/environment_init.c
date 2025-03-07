 #include <environment.h>
 #include <app.h>
 #include <SDL_image.h>

    // Define the environment

 int Environment_AnimationInit() {
    // Initialize the environment
    environment.walls = NULL;
    environment.wallCount = 0;

    // Load the brick texture
    SDL_Texture* brickTexture = IMG_LoadTexture(app.setup.renderer, "Assets/Images/wall.png");
    if (!brickTexture) {
        SDL_Log("Failed to load brick texture: %s", SDL_GetError());
        return 0; // Initialization failed
    }

    // Define the position and size of the rectangle
    SDL_Rect wallSize = {100, 100, 200, 50}; // Position (100, 100), width 200, height 50
    SDL_Rect hitbox = wallSize; // Use the same size for the hitbox

    // Create a wall with the brick texture
    Wall wall;
    wall.wallSize = wallSize;
    wall.hitbox = hitbox;
    wall.texture = brickTexture;

    // Add the wall to the environment
    Environment_AddWall(wall);

    return 1; // Initialization successful
}

 

