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

- **Vector Addition/Subtraction**: Combines vectors component-wise. Used extensively for physics calculations such as applying velocity to position.
  ```c
  Vec2 Vec2_Add(Vec2 a, Vec2 b) {
      Vec2 result = { a.x + b.x, a.y + b.y };
      return result;
  }
  ```

- **Normalization**: Converts a vector to a unit vector (length of 1) while preserving direction. Critical for directional calculations like aiming and movement.
  ```c
  Vec2 Vec2_Normalize(Vec2 v) {
      float magnitude = Vec2_Magnitude(v);
      if (magnitude > 0) {
          Vec2 result = { v.x / magnitude, v.y / magnitude };
          return result;
      }
      return v;  // Avoid division by zero
  }
  ```

- **Dot Product**: Calculates the scalar product of two vectors, used for angle calculations and projection.
  ```c
  float Vec2_Dot(Vec2 a, Vec2 b) {
      return a.x * b.x + a.y * b.y;
  }
  ```

- **Distance Calculation**: Measures the Euclidean distance between two points. Used for proximity checks and collision detection.
  ```c
  float Vec2_Distance(Vec2 a, Vec2 b) {
      float dx = b.x - a.x;
      float dy = b.y - a.y;
      return sqrtf(dx*dx + dy*dy);
  }
  ```

- **Linear Interpolation (Lerp)**: Creates smooth transitions between two vectors. Used for camera movement, animations, and particle effects.
  ```c
  Vec2 Vec2_Lerp(Vec2 a, Vec2 b, float t) {
      // Clamp t between 0 and 1
      t = t < 0 ? 0 : (t > 1 ? 1 : t);
      Vec2 result = {
          a.x + (b.x - a.x) * t,
          a.y + (b.y - a.y) * t
      };
      return result;
  }
  ```

Located in `include/Core/vec2.h` and implemented in `src/Core/vec2.c`.

### Collision System {#collision_system}
The collision system detects interactions between game objects using a layer-based filtering approach:

```c
typedef struct {
    SDL_Rect hitbox;            // The hitbox of the collider
    CollisionLayer layer;       // What layer this object belongs to
    CollisionLayer collidesWith; // Bitmask of layers this can collide with
    void* owner;                // Pointer back to the entity
    bool active;                // Is this collidable active?
} Collider;

typedef struct {
    Collider* objects[MAX_COLLISIONS_PER_CHECK]; // An array of detected colliders
    int count;                                   // Number of collisions detected
} ColliderCheckResult;
```

Key algorithms include:

- **Collider Registration**: Manages a centralized registry of active colliders for efficient collision checking.
  ```c
  void Collider_Register(Collider* collider, void* owner) {
      if (ColliderCount >= MAX_COLLIDABLES) {
          printf("Error: Maximum collidables reached\n");
          return;
      }

      // Find first available slot
      int id = 0;
      while (id < MAX_COLLIDABLES) {
          if (ColliderList[id] == NULL) break;
          if (!ColliderList[id]->active) break;
          id++;
      }
      collider->active = true;
      collider->owner = owner;
      ColliderList[id] = collider;
      if (id >= ColliderCount) ColliderCount = id + 1;
  }
  ```

- **Layer-Based Collision Detection**: Uses bitmasks to efficiently filter which types of objects can collide with each other.
  ```c
  bool Collider_Check(Collider* collider, ColliderCheckResult* checkResult) {
      if (!collider->active) return false;
      
      bool selfFound = false;
      if (checkResult != NULL) {
          checkResult->count = 0;
      }

      // Check against all other collidables
      for (int i = 0; i < ColliderCount; i++) {
          if (ColliderList[i] == collider) {
              selfFound = true;
              continue;
          } // Skip input collider
          if (checkResult != NULL && checkResult->count >= MAX_COLLISIONS_PER_CHECK) continue;
          if (!ColliderList[i]->active) continue; // Skip inactive colliders
          
          // Bitwise AND to check if the layers match for collision
          if ((collider->collidesWith & ColliderList[i]->layer) == 0) continue;
          
          // Perform actual rectangle intersection check
          if (SDL_HasIntersection(&collider->hitbox, &ColliderList[i]->hitbox)) {
              if (checkResult == NULL) return true;
              checkResult->objects[checkResult->count++] = ColliderList[i];
          }
      }
      
      if (!selfFound) {
          SDL_Log("Warning: Collider object not found in registry\n");
          return false;
      }
      
      return checkResult != NULL && checkResult->count > 0;
  }
  ```

- **Collision Management Workflow**: The typical workflow for using the collision system involves:
  1. Creating a collider with appropriate layers
  2. Registering it with the collision system
  3. Updating its position during gameplay
  4. Checking for collisions against other objects
  5. Taking appropriate action based on collision results

  ```c
  // Example usage in player code:
  
  // 1. Create a collider (typically done once during initialization)
  Collider playerCollider = {
      .hitbox = {0, 0, 20, 20},
      .layer = COLLISION_LAYER_PLAYER,
      .collidesWith = COLLISION_LAYER_ENVIRONMENT | COLLISION_LAYER_ENEMY
  };
  
  // 2. Register it (typically done once during initialization)
  Collider_Register(&playerCollider, &player);
  
  // 3. Update position (done every frame)
  playerCollider.hitbox.x = (int)(player.state.position.x - playerCollider.hitbox.w/2);
  playerCollider.hitbox.y = (int)(player.state.position.y - playerCollider.hitbox.h/2);
  
  // 4. Check for collisions (done when needed)
  ColliderCheckResult result;
  if (Collider_Check(&playerCollider, &result)) {
      // 5. Handle collisions
      for (int i = 0; i < result.count; i++) {
          Collider* other = result.objects[i];
          
          // Act based on collision layer
          if (other->layer == COLLISION_LAYER_ENVIRONMENT) {
              // Handle environment collision (e.g., stop movement)
          } else if (other->layer == COLLISION_LAYER_ENEMY) {
              // Handle enemy collision (e.g., take damage)
          }
      }
  }
  ```

- **Collision Cleanup**: Manages the lifecycle of colliders, allowing them to be properly deactivated when no longer needed.
  ```c
  void Collider_Reset(Collider* collider) {
      collider->active = false;
      collider->owner = NULL;
      collider->layer = COLLISION_LAYER_NONE;
      collider->collidesWith = COLLISION_LAYER_NONE;
  }
  ```

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
    float rotation;
    float angularVelocity;
    float drag;
    SDL_Texture* texture;
} Particle;

typedef struct {
    Particle* particles;
    int maxParticles;
    int activeParticles;
    Vec2 position;
    Vec2 emissionDirection;
    float emissionAngle;
    float emissionRate;
    float emissionTimer;
    ParticleMovementPattern movementPattern;
    ParticleEmitterPreset preset;
    bool isActive;
} ParticleEmitter;
```

Key algorithms include:

- **Particle Emission**: Controls how particles are spawned, including patterns like burst, continuous streams, or shaped emissions.
  ```c
  void Particle_Emit(ParticleEmitter* emitter, int count, Vec2 position) {
      for (int i = 0; i < count; i++) {
          if (emitter->activeParticles >= emitter->maxParticles) {
              break;
          }
          
          // Find an inactive particle slot
          int index = -1;
          for (int j = 0; j < emitter->maxParticles; j++) {
              if (emitter->particles[j].currentLife <= 0) {
                  index = j;
                  break;
              }
          }
          
          if (index == -1) continue;
          
          // Initialize particle with random variations based on emitter properties
          Particle* p = &emitter->particles[index];
          p->position = position;
          
          // Calculate emission angle with randomness
          float angle = emitter->emissionDirection + 
                        (Random_Float(-emitter->emissionAngle, emitter->emissionAngle) * 0.5f);
          
          float speed = Random_Float(emitter->minSpeed, emitter->maxSpeed);
          p->velocity.x = cosf(angle) * speed;
          p->velocity.y = sinf(angle) * speed;
          
          // Set other particle properties with randomness
          p->lifetime = Random_Float(emitter->minLifetime, emitter->maxLifetime);
          p->currentLife = p->lifetime;
          // ...more initialization...
          
          emitter->activeParticles++;
      }
  }
  ```

- **Particle Movement Patterns**: Implements different movement behaviors like linear, spiral, gravitational, or targeted movement.
  ```c
  void Particle_UpdateMovement(Particle* particle, ParticleMovementPattern pattern) {
      switch (pattern) {
          case PATTERN_LINEAR:
              // Simple linear movement with drag
              particle->velocity.x *= (1.0f - particle->drag * Time->deltaTimeSeconds);
              particle->velocity.y *= (1.0f - particle->drag * Time->deltaTimeSeconds);
              particle->position = Vec2_Add(particle->position, 
                  Vec2_Scale(particle->velocity, Time->deltaTimeSeconds));
              break;
              
          case PATTERN_SPIRAL:
              // Spiral movement pattern
              float angle = atan2f(particle->velocity.y, particle->velocity.x);
              angle += particle->angularVelocity * Time->deltaTimeSeconds;
              float speed = Vec2_Magnitude(particle->velocity);
              particle->velocity.x = cosf(angle) * speed;
              particle->velocity.y = sinf(angle) * speed;
              particle->position = Vec2_Add(particle->position, 
                  Vec2_Scale(particle->velocity, Time->deltaTimeSeconds));
              break;
              
          // ...other patterns...
      }
  }
  ```

- **Particle Lifecycle Management**: Handles particle creation, updating, and removal based on lifetime.
  ```c
  void Particle_Update(ParticleEmitter* emitter) {
      // Emit new particles based on emission rate
      emitter->emissionTimer += Time->deltaTimeSeconds;
      if (emitter->isActive && emitter->emissionTimer >= 1.0f / emitter->emissionRate) {
          emitter->emissionTimer = 0;
          Particle_Emit(emitter, 1, emitter->position);
      }
      
      // Update existing particles
      int activeCount = 0;
      for (int i = 0; i < emitter->maxParticles; i++) {
          Particle* p = &emitter->particles[i];
          
          if (p->currentLife <= 0) continue;
          
          // Decrease lifetime
          p->currentLife -= Time->deltaTimeSeconds;
          if (p->currentLife <= 0) {
              continue;  // Particle is now inactive
          }
          
          // Update movement
          Particle_UpdateMovement(p, emitter->movementPattern);
          
          // Update other properties like color, size, rotation
          float lifeRatio = p->currentLife / p->lifetime;
          p->size = Lerp(p->endSize, p->startSize, lifeRatio);
          p->rotation += p->angularVelocity * Time->deltaTimeSeconds;
          
          // Color interpolation from start to end color
          p->color.r = Lerp(p->endColor.r, p->startColor.r, lifeRatio);
          p->color.g = Lerp(p->endColor.g, p->startColor.g, lifeRatio);
          p->color.b = Lerp(p->endColor.b, p->startColor.b, lifeRatio);
          p->color.a = Lerp(p->endColor.a, p->startColor.a, lifeRatio);
          
          activeCount++;
      }
      
      emitter->activeParticles = activeCount;
  }
  ```

- **Particle Rendering**: Efficiently renders particles with various blending modes and visual effects.
  ```c
  void Particle_Render(ParticleEmitter* emitter) {
      for (int i = 0; i < emitter->maxParticles; i++) {
          Particle* p = &emitter->particles[i];
          
          if (p->currentLife <= 0) continue;
          
          // Convert world coordinates to screen coordinates
          Vec2 screenPos = Camera_WorldVecToScreen(p->position);
          
          // Set color with alpha blending
          SDL_SetTextureColorMod(p->texture, p->color.r, p->color.g, p->color.b);
          SDL_SetTextureAlphaMod(p->texture, p->color.a);
          
          // Create destination rectangle
          SDL_Rect destRect = {
              (int)(screenPos.x - p->size / 2),
              (int)(screenPos.y - p->size / 2),
              (int)p->size,
              (int)p->size
          };
          
          // Render with rotation if needed
          if (p->rotation != 0) {
              SDL_RenderCopyEx(
                  app.resources.renderer,
                  p->texture,
                  NULL,
                  &destRect,
                  p->rotation * (180.0f / M_PI),  // Convert radians to degrees
                  NULL,
                  SDL_FLIP_NONE
              );
          } else {
              SDL_RenderCopy(app.resources.renderer, p->texture, NULL, &destRect);
          }
      }
  }
  ```

Located in `include/Utilities/Particles/particle.h` and implemented in `src/Utilities/Particles/particle.c`.

### Map Generation {#map_generation}
The map system manages the game environment using a three-tiered hierarchical structure: maps, chunks, and tiles.

#### Map-Chunk-Tile Hierarchy
The map is divided into chunks, and each chunk is further divided into tiles. This hierarchical structure allows for efficient management and rendering of the game environment.

- **Map**: The entire game world, consisting of multiple chunks.
- **Chunk**: A section of the map, containing a grid of tiles.
- **Tile**: The smallest unit of the map, representing a single piece of the environment.

```c
typedef struct {
    int type;
    bool collidable;
    SDL_Texture* texture;
    int variation;
    bool explored;
} Tile;

typedef struct {
    Tile** tiles;
    int width;
    int height;
    Vec2 position;
    bool isRoom;
    RoomType roomType;
    int colliderCount;
    Collider** colliders;
} MapChunk;

typedef struct {
    MapChunk** chunks;
    int chunkWidth;
    int chunkHeight;
    int chunkSize;
    Vec2 startPos;
    Vec2 endPos;
    Vec2* mainPath;
    int mainPathLength;
    int currentChunkX;
    int currentChunkY;
} EnvironmentMap;
```

hm to find the path from the start node to the end node.
4. **Reconstruct Path**: Reconstructs the path fro#### Procedural Map Generation
The map generation process creates randomized but cohesive game levels using a combination of techniques.

1. **Reset Existing Map Data**: Clears any existing map data to start fresh.
2. **Place Starter Room**: Places the starter room in a fixed location, typically the center of the map.
3. **Create Main Path**: Uses a directed random walk to create the main path from the start room to the end room.
4. **Place End Room**: Places the end room at the furthest point on the main path.
5. **Fill in Side Paths and Additional Rooms**: Adds side paths and additional rooms to create a more complex map.
6. **Add Detail to Each Chunk**: Adds details to each chunk based on its type.
7. **Place Colliders**: Places colliders for walls and obstacles.


## Conclusion {#conclusion}
This documentation provides a high-level overview of Operation Null Mind's architecture and key components. For detailed information about specific functions and structures, please refer to the appropriate sections of this documentation or the inline comments in the source code.

For developers new to the project, we recommend starting with the [Project Structure](#structure) section to understand the codebase organization, then exploring the [Application Lifecycle](#lifecycle) to understand the flow of execution. The [Key Algorithms and Data Structures](#algorithms) section provides deeper insights into the technical implementation details.

If you're interested in contributing to the project, please refer to the GitHub repository for contribution guidelines and development roadmap.


