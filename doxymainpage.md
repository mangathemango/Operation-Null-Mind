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
                   • Defines the interface for all modules
                   • Contains struct definitions, function declarations, and constants
                   • Organized to mirror the src directory structure

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
    bool isRunning;           // Controls the main game loop
    SDL_Window* window;       // Main game window
    SDL_Renderer* renderer;   // Renderer for drawing to window
    SDL_Texture* target;      // Render target for camera effects
    SDL_Rect viewport;        // Current viewport dimensions
    // Other application state variables
} AppData;

extern AppData app;  // Global app instance
```

Located in `include/App/app.h` and defined in `src/App/app.c`.

### InputData {#input_data}
Tracks all input device states for handling player interactions:

```c
typedef struct {
    MouseData mouse;          // Mouse position and button states
    KeyboardData keyboard;    // Keyboard key states
    // Additional input device states
} InputData;

extern InputData* Input;  // Global input instance
```

Located in `include/Core/input.h` and defined in `src/Core/input.c`.

### TimeData {#time_data}
Manages timing information for frame-rate independence:

```c
typedef struct {
    uint32_t currentTime;     // Current frame time
    uint32_t lastTime;        // Previous frame time
    float deltaTimeSeconds;   // Time between frames in seconds
    float timeScale;          // Time scaling factor
    // Other timing variables
} TimeData;

extern TimeData* Time;  // Global time instance
```

Located in `include/Core/time.h` and defined in `src/Core/time.c`.

### CameraData {#camera_data}
Controls the game's view into the world:

```c
typedef struct {
    Vec2 position;            // Camera position in world
    float zoom;               // Camera zoom level
    SDL_Rect viewport;        // Camera viewport
    // Other camera properties
} CameraData;

extern CameraData* Camera;  // Global camera instance
```

Located in `include/Core/camera.h` and defined in `src/Core/camera.c`.

### PlayerData {#player_data}
Contains all information about the player character:

```c
typedef struct {
    Vec2 position;            // Player position
    Vec2 velocity;            // Player movement velocity
    float health;             // Current health
    PlayerState state;        // Current player state
    // Other player properties
} PlayerData;

extern PlayerData player;  // Global player instance
```

Located in `include/Game/player.h` and defined in `src/Game/player.c`.

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


