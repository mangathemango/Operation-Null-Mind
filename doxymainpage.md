# Technical Documentation {#mainpage}

@tableofcontents

## Overview {#introduction}
Operation Null Mind is a 2D top-down shooter with roguelike elements, developed in C utilizing the SDL2 framework. 

![Gameplay](gameplay.png){width=400px}

This comprehensive documentation aims to provide developers with a detailed understanding of the codebase architecture, including:

- Project structural organization
- Application execution flow and lifecycle
- Critical global variables and state management
- Core algorithms, data structures, and implementation details

This documentation is designed to facilitate efficient navigation and comprehension of the codebase for both new and experienced contributors to the project.

## Navigating This Documentation {#navigation}
This documentation is generated using Doxygen and offers several navigation methods:

- **Table of Contents**: Navigate through this page through this table of contents

![Table of Contents](table_of_contents.png){width=400px}

- **[Class List](annotated.html)**: View a list of all the structs in the project

![Class List](class_list.png){width=400px}

- **[File List](files.html)**: View a list of all the files in the project

![File List](file_list.png){width=400px}

- **Search Function**: Use the search box in the upper right corner to find specific elements

![Search Box](search_box.png){width=400px}

**Note**: The "All" search option in Doxygen is not really good. You may have to adjust the search categories like this.

![Search Issues](search_issues.png){width=400px}

- **[Index](index.html)**: View an alphabetical list of all the elements in the project

![Index](index.png){width=400px}

- **[Function Index](functions.html)**: View an alphabetical list of all the functions in the project

![Function Index](function_index.png){width=400px}

- **Breadcrumbs**: Use the breadcrumbs at the bottom of the page to navigate back to the main page

![Breadcrumbs](breadcrumbs.png){width=400px}

## Project Structure {#structure}
The project is organized into several directories, each with a specific purpose:

```
/Assets         -> Contains images, sfx, music, ...
                   • All game resources are stored here
                   • Organized by resource type (images, sounds, fonts)
                   • Assets are loaded at runtime by the respective systems

/include        -> Contains header (.h) files
    /App        -> Application headers for game loop management
    /Core       -> Core system headers (vectors, time, etc.)
    /Game       -> Game mechanics headers (player, gun, etc.)
    /Utilities  -> Helper utilities headers (animation, ...)

/src            -> Contains source (.c) files
                   • Implements functionality declared in the header files
                   • Follows the same organizational structure as include/

    /App        -> Handles the main game loop
                   • Implements the application lifecycle (start, update, render, quit)
                   • Coordinates all other systems

    /Core       -> Core systems, like vectors, time, ...
                   • Implementation of fundamental systems like input, physics, etc.
                   • Used by virtually all other parts of the codebase

    /Game       -> Game mechanics, like player, gun, ...
                   • Implementation of gameplay features
                   • Depends on Core systems but is independent of App logic

    /Utilities  -> Helper utilities, like animation, ...
                   • Provides services to both Core and Game modules

    main.c      -> The entry point of the program
                   • Contains (kinda) the main() function
                   • Calls functions defined in App/ to run the game
```

This modular organization follows a clear separation of concerns, making the codebase maintainable and extensible. The structure allows for:

1. **Clear dependencies**: Core systems don't depend on Game systems, avoiding circular dependencies
2. **Modularity**: Systems can be modified or replaced without affecting unrelated components
3. **Scalability**: New modules and features can be added by following the established patterns
4. **Readability**: Developers can quickly locate code by understanding its category

## Application Lifecycle {#lifecycle}
The application lifecycle is managed by the `App` module, which coordinates the game loop and system initialization. The lifecycle consists of the following stages:

### Initialization Stage [Start] {#init_stage}
During initialization, all systems are set up and resources are loaded:

1. **SDL Initialization**: SDL libraries (SDL2, SDL_image, SDL_ttf, etc.) are initialized
2. **Resource Loading**: Game assets (textures, sounds, fonts) are loaded into memory
3. **System Initialization**: Core systems like input, time, camera, and collision are set up
4. **Game State Setup**: Initial game state, player, maps, and other game objects are created

All initialization functions are called from `App_Start()` in `src/App/app_start.c`.

### Game Loop {#game_loop}
Once initialized, the game enters its main loop which runs continuously until exit:

#### Pre-Update [PreUpdate] {#pre_update}
Before processing the main game logic, the pre-update stage:
- Resets frame-specific states
- Updates timing information
- Prepares the renderer for the new frame

These operations are coordinated by `App_PreUpdate()` in `src/App/app_preupdate.c`.

#### Event Handling [Event_Handler] {#event_handling}
Event handling processes all user inputs and system events:
- Keyboard and mouse inputs are captured
- Window events (resize, focus, etc.) are processed
- Input state is updated for use in the main game logic

Event handling is managed by `App_Event_Handler()` in `src/App/app_event_handler.c`.

#### Post-Update [PostUpdate] {#post_update}
The post-update stage contains the main game logic:
- Player movement and actions
- Enemy AI and behavior
- Physics and collision detection
- Game state updates

These operations are orchestrated by `App_PostUpdate()` in `src/App/app_postupdate.c`.

#### Rendering [Render] {#rendering}
After all game logic is processed, the rendering stage:
- Clears the screen
- Renders the game world (map, entities, effects)
- Draws the UI
- Presents the final frame to the display

Rendering is managed by `App_Render()` in `src/App/app_render.c`.

### Shutdown Stage [Quit] {#shutdown_stage}
When the game exits, cleanup operations free resources and shut down systems:
- Unload assets from memory
- Close file handles
- Free allocated memory
- Shut down SDL and other libraries

Cleanup is handled by `App_Quit()` in `src/App/app_quit.c`.

## Key Global Variables {#global_vars}
Operation Null Mind uses several global variables to maintain state across the application. These variables are declared as `extern` in header files and defined in their respective source files.

### AppData {#app_data}
The central application data structure that holds the game's current state:

```c
typedef struct {
    AppResources resources;  // Contains window, renderer, textures, fonts
    AppState state;          // Contains running flag, fps, current scene
    AppConfig config;        // Contains window settings and debug flags
} AppData;

extern AppData app;  // Global app instance
```

Located in `include/App/app.h` and defined in `src/App/app.c`. This is the central structure that manages the application state and resources.

**Usage Examples:**
```c
// Change the game state
app.state.currentScene = SCENE_PAUSE;

// Check if the application is still running
if (!app.state.running) {
    // Handle exit condition
}

// Access the renderer for drawing
SDL_RenderClear(app.resources.renderer);

// Use the configured screen dimensions
int width = app.config.screen_width;
int height = app.config.screen_height;
```

### InputEvent {#input_data}
Tracks all input device states for handling player interactions:

```c
typedef struct {
    MouseState mouse;       // Contains position, motion, button states
    KeyboardState keyboard; // Contains states for all keyboard keys
} InputEvent;

extern const InputEvent * const Input;  // Global input instance (read-only)
```

Located in `include/Core/input.h` and defined in `src/Core/input.c`. The Input system provides an interface for checking if keys/buttons are pressed, held, or released.

**Usage Examples:**
```c
// Check if a key was just pressed this frame
if (Input->keyboard.keys[SDL_SCANCODE_SPACE].pressed) {
    Player_Jump();
}

// Check if a key is being held down
if (Input->keyboard.keys[SDL_SCANCODE_W].held) {
    Player_MoveForward();
}

// Check if a key was just released
if (Input->keyboard.keys[SDL_SCANCODE_ESCAPE].released) {
    TogglePauseMenu();
}

// Get current mouse position
Vec2 mousePos = Input->mouse.position;

// Check if left mouse button was just clicked
if (Input->mouse.leftButton.pressed) {
    Player_Shoot();
}
```

### TimeSystem {#time_data}
Manages timing information for frame-rate independence:

```c
typedef struct {
    float deltaTimeSeconds;      // Time between frames in seconds
    float timeScale;             // Scale factor for time
    float scaledDeltaTimeSeconds; // Delta time multiplied by time scale
    double programElapsedTimeSeconds; // Total time since program start
    double previousTick;         // Previous frame tick value
} TimeSystem;

extern const TimeSystem * const Time;  // Global time instance (read-only)
```

Located in `include/Core/time_system.h` and defined in `src/Core/time_system.c`. The Time system is crucial for frame-rate independent movement and animations.

**Usage Examples:**
```c
// Move an object with frame-rate independence
object.position.x += object.velocity.x * Time->deltaTimeSeconds;
object.position.y += object.velocity.y * Time->deltaTimeSeconds;

// Update animation timer
animation.timer += Time->deltaTimeSeconds;
if (animation.timer >= animation.frameDuration) {
    animation.currentFrame = (animation.currentFrame + 1) % animation.frameCount;
    animation.timer = 0;
}

// Create a countdown timer
float countdownRemaining = 10.0f - Time->programElapsedTimeSeconds;
if (countdownRemaining <= 0) {
    // Time's up!
}

// Use time scaling for slow-motion effect
Time_SetTimeScale(0.5f); // Half speed
// Movement and animations will now use scaledDeltaTimeSeconds automatically
```

### CameraSystem {#camera_data}
Controls the game's view into the world:

```c
typedef struct {
    Vec2 position;  // Camera position in world coordinates
} CameraSystem;

extern CameraSystem camera;  // Global camera instance
```

Located in `include/Core/camera.h` and defined in `src/Core/camera.c`. The Camera system provides coordinate conversion between world and screen space.

**Usage Examples:**
```c
// Update camera to follow player
camera.position = player.state.position;

// Convert world position to screen position for rendering
Vec2 worldPos = enemy.position;
Vec2 screenPos = Camera_WorldVecToScreen(worldPos);
SDL_Rect destRect = {screenPos.x, screenPos.y, enemy.width, enemy.height};
SDL_RenderCopy(app.resources.renderer, enemy.texture, NULL, &destRect);

// Convert screen position (e.g., mouse) to world position
Vec2 mouseScreenPos = Input->mouse.position;
Vec2 mouseWorldPos = Camera_ScreenVecToWorld(mouseScreenPos);

// Check if an object is visible on screen
SDL_Rect objectRect = {worldPos.x, worldPos.y, object.width, object.height};
if (Camera_RectIsOnScreen(objectRect)) {
    // Only render if visible
    RenderObject(object);
}
```

### PlayerData {#player_data}
Contains all information about the player character:

```c
typedef struct {
    PlayerState state;      // Position, direction, speed, equipped gun, etc.
    PlayerStat stats;       // Walk speed, dash speed, dash duration, etc.
    PlayerResources resources; // Particle emitters, timers, animations, etc.
    AnimationData animData; // Animation data for the player
} PlayerData;

extern PlayerData player;  // Global player instance
```

Located in `include/Game/player.h` and defined in `src/Game/player.c`. The Player system manages the player character's state, movement, animations, and interactions.

**Usage Examples:**
```c
// Access player position
Vec2 playerPos = player.state.position;

// Move the player
player.state.position.x += movementX;
player.state.position.y += movementY;

// Change player's weapon
player.state.currentGun = &Gun_Shotgun;

// Check if player is dashing
if (player.state.dashing) {
    // Apply dash effects
    CreateDashParticles();
}

// Apply damage to player
void Player_TakeDamage(float amount) {
    player.state.health -= amount;
    if (player.state.health <= 0) {
        Player_Die();
    }
}

// Start player dash
if (Input->keyboard.keys[SDL_SCANCODE_LSHIFT].pressed) {
    Player_Dash();
}
```

## Key Algorithms and Data Structures {#algorithms}

### Vector System {#vector_system}
The vector system provides 2D vector operations essential for game physics and positioning:

```c
typedef struct {
    float x;
    float y;
} Vec2;
```

Key algorithms include:
- Vector addition/subtraction
- Normalization
- Dot and cross products
- Distance calculations
- Linear interpolation (lerp)

Located in `include/Core/vec2.h` and implemented in `src/Core/vec2.c`.

### Collision System {#collision_system}
The collision system detects and resolves interactions between game objects:

```c
typedef struct {
    Vec2 position;
    Vec2 size;
    // Additional properties
} BoxCollider;

typedef struct {
    Vec2 position;
    float radius;
    // Additional properties
} CircleCollider;
```

Key algorithms include:
- Box-box collision detection
- Circle-circle collision detection
- Box-circle collision detection
- Ray casting
- Swept collision testing

Located in `include/Core/colliders.h` and implemented in `src/Core/colliders.c`.

### Particle System {#particle_system}
The particle system creates visual effects like explosions, smoke, and bullet trails:

```c
typedef struct {
    Vec2 position;
    Vec2 velocity;
    float lifetime;
    float currentLife;
    SDL_Color color;
    float size;
    // Additional properties
} Particle;

typedef struct {
    Particle* particles;
    int maxParticles;
    int activeParticles;
    // Emitter properties
} ParticleEmitter;
```

Key algorithms include:
- Particle emission patterns (burst, stream, etc.)
- Particle movement and physics
- Particle lifetime management
- Color and size interpolation

Located in `include/Utilities/Particles/particle.h` and implemented in `src/Utilities/Particles/particle.c`.

### Map Generation {#map_generation}
The map system manages the game environment and procedural generation:

```c
typedef struct {
    int type;
    bool collidable;
    // Tile properties
} Tile;

typedef struct {
    Tile** tiles;
    int width;
    int height;
    // Chunk properties
} MapChunk;

typedef struct {
    MapChunk** chunks;
    int chunkWidth;
    int chunkHeight;
    // Map properties
} EnvironmentMap;
```

Key algorithms include:
- Procedural map generation
- Room and corridor placement
- Tile-based collision detection
- Map rendering optimization
- Pathfinding (A* algorithm)

Located in `include/Game/Environment/maps.h` and implemented in `src/Game/Environment/maps.c`.

### Animation System {#animation_system}
The animation system manages sprite animations for game entities:

```c
typedef struct {
    SDL_Rect* frames;
    int frameCount;
    int currentFrame;
    float frameDuration;
    float timer;
    bool loop;
    // Animation properties
} Animation;
```

Key algorithms include:
- Frame-based animation playback
- Animation timing and control
- Sprite sheet management
- Animation blending and transitions

Located in `include/Utilities/animation.h` and implemented in `src/Utilities/animation.c`.

## Conclusion {#conclusion}
This documentation provides a high-level overview of Operation Null Mind's architecture and key components. For detailed information about specific functions and structures, please refer to the appropriate sections of this documentation or the inline comments in the source code.

For developers new to the project, we recommend starting with the [Project Structure](#structure) section to understand the codebase organization, then exploring the [Application Lifecycle](#lifecycle) to understand the flow of execution. The [Key Algorithms and Data Structures](#algorithms) section provides deeper insights into the technical implementation details.

If you're interested in contributing to the project, please refer to the GitHub repository for contribution guidelines and development roadmap.


