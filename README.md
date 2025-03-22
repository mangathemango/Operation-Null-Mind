# Operation Null Mind

Note: If you're viewing this through a zip file, this file looks a lot better on the github repository description:

## Table of Contents

- [Controls](#controls)
- [How to Run the Game](#how-to-run-the-game)
- [About the Codebase](#about-the-codebase)
  - [Code Structure](#code-structure)
  - [Understanding the Code Flow](#understanding-the-code-flow)
- [Function Naming Convention](#function-naming-convention)
  - [[Start]](#start)
  - [[PreUpdate]](#preupdate)
  - [[Event_Handler]](#event_handler)
  - [[PostUpdate]](#postupdate)
  - [[Render]](#render)
  - [[Quit]](#quit)
  - [[Utilities]](#utilities-1)
  - [[?]](#)
- [Key Modules Overview](#key-modules-overview)
  - [App Module](#app-module)
  - [Core Modules](#core-modules)
  - [Game Modules](#game-modules)
  - [Utilities](#utilities)
- [Key C Concepts Used in This Project](#key-c-concepts-used-in-this-project)
  - [Pointers and Memory Management](#pointers-and-memory-management)
  - [Structures](#structures)
- [How to Install &amp; Compile for Windows](#how-to-install--compile-for-windows)
  - [Step 1: Clone Repository](#step-1-clone-repository)
  - [Step 2: Install cmake and MingW](#step-2-install-cmake-and-mingw)
  - [Step 3: Build, Compile and Run](#step-3-build-compile-and-run)

## How to run the game:

Pretty easy, just click on build/Operation-Null-Mind.exe

## Controls:

WASD - Move character

Left click - Shoot

1 2 3 4 5 -  Switch weapons (for now)

Shift  - Skill 1 (Dash)

## About the codebase:

Most of everything (around 90%) inside the codebase is already pretty well documented. But generally, if you want to look around on how everything works, you should start on src/main.c (which contains the game loop), then everything inside include/app.h and the folder src/App/, then everything else inbetween.

### Code Structure

This project follows a modular structure to keep the code organized:

```
/Assets         -> Contains images, sfx, music, ...
/include        -> Contains header (.h) files
    ...
/src            -> Contains source (.c) files
    /App        -> Handles the main game loop
    /Core       -> Core systems, like vectors, time, ...
    /Game       -> Game mechanics, like player, gun, ...
    /Utilities  -> Helper utilities, like animation, ...
    main.c      -> The entry point of the program.
                   The program will start with this file.
```

### Understanding the Code Flow

The game follows this general flow:

1. **Initialization**: Set up SDL, load resources, initialize game state. This is done inside the App_Start() function.
2. **Game Loop**: Process events, update game state, render graphics. This is done inside the App_PreUpdate(), App_Event_Handler(), App_PostUpdate(), and App_Render().
3. **Cleanup**: Free resources and shut down the program. This is done inside the App_Quit().

## Function Naming Convention:

All of our functions are labelled with tags that indicate when they are called in the game lifecycle:

### [Start]

These functions are called once at the start of the program, used for data initialization and the like. Every [Start] functions should be called somewhere inside app_start.c

**Example**: `Player_Start()` initializes the player's health, position, and abilities.

### [PreUpdate]

These functions are called ***every frame*** before everything else. This is mainly functions used as a SETUP for the current frame, rather than handling the main logic. This includes resetting some booleans, positions, etc.

**Example**: `Input_PreUpdate()` resets input states at the beginning of each frame.

### [Event_Handler]

Event_Handler are called ***every frame*** whenever there's an event detected, like mouse click, key board press, etc.

**For beginners**: Think of events as signals that something happened (like a key press). The event handler catches these signals and updates our game accordingly.

*Right now, App_Event_handler is only used to quit the program and update our Input struct inside Core/input.c. The Input struct tells you everything about what's going on with the keyboard and mouse - whether a button was just pressed/released, or whether it is being held. This allows for more flexible event handling - without having to pass the SDL_Event struct on all the functions that requires player input.*

### [PostUpdate]

These functions are called every frame to handle the main logic of the frame - for example updating player's position, gun rotation, input handling, etc.

**Example**: `Player_PostUpdate()` updates the player's position based on input and handles collisions.

### [Render]

Well, those functions are called every frame just to render stuff. Quite simple.

**Example**: `Player_Render()` draws the player character at its current position.

### [Quit]

And these functions, well, is called at the end of the program. This mostly includes functions that free up memory of something (though we havent worked on that yet)

**For beginners**: In C, you need to manually free memory that you've allocated. These functions make sure we don't have memory leaks.

### [Utilities]

These functions are called basically anywhere - and acts as a helper function for other functions.

**Example**: `Vec2_Distance()` calculates the distance between two points.

### [?]

Some tags have this ? thing (like [PostUpdate?]), which says that they are called every frame only if a certain condition are met.

## Key Modules Overview

This section provides an overview of the main modules that make up the game. Understanding these key components will help you navigate the codebase more effectively.

### App Module

The App module is the core orchestrator of the game. It manages the game lifecycle and ties all other modules together.

**Key Files:**

- `include/App/app.h` - Main application header defining the AppData structure and function prototypes
- `src/App/app_start.c` - Initialization logic that runs once at startup
- `src/App/app_preupdate.c` - Frame setup logic that runs before processing game logic
- `src/App/app_event_handler.c` - Handles SDL events like keyboard/mouse input
- `src/App/app_postupdate.c` - Main game logic that runs each frame
- `src/App/app_render.c` - Rendering logic that draws everything to the screen
- `src/App/app_quit.c` - Cleanup logic that runs when the game exits

**For Beginners:**
The App module is like the conductor of an orchestra - it doesn't make music itself, but it coordinates all the other modules to work together.

### Core Modules

Core modules provide fundamental functionality that the rest of the game relies on. They handle basic operations like math, input, and rendering.

**Key Components:**

1. **Vector System** (`include/Core/vec2.h`, `src/Core/vec2.c`)

   - Provides 2D vector operations like addition, subtraction, normalization
   - Used for positions, movement, and direction calculations
   - Example: `Vec2_Add()` combines two vectors, useful for adding velocity to position
2. **Input System** (`include/Core/input.h`, `src/Core/input.c`)

   - Tracks keyboard and mouse state
   - Distinguishes between keys just pressed, held down, or just released
   - Example: `Input->mouse.leftButton.pressed` is true on the first frame the left mouse button is pressed
3. **Time System** (`include/Core/time.h`, `src/Core/time.c`)

   - Manages game timing, delta time, and frame rate
   - Ensures consistent game speed regardless of frame rate
   - Example: `Time->deltaTimeSeconds` returns the time elapsed since the last frame
4. **Camera System** (`include/Core/camera.h`, `src/Core/camera.c`)

   - Handles viewport and screen-to-world coordinate transformations
   - Manages camera movement, zoom, and following objects
   - Example: `Camera_WorldToScreen()` converts world coordinates to screen coordinates
5. **Colliders System** (`include/Core/colliders.h`, `src/Core/colliders.c`)

   - Provides collision detection between game entities
   - Supports different collider shapes (rectangles, circles)
   - Example: `Collider_CheckRectRect()` tests if two rectangle colliders intersect
6. **Sound System** (`include/Core/sound.h`, `src/Core/sound.c`)

   - Manages audio playback for music and sound effects
   - Handles loading, playing, and stopping audio files
   - Example: `Sound_PlaySFX()` plays a sound effect with optional volume control
7. **UI System** (`include/Core/UI/UI_text.h`, `src/Core/UI/UI_text.c`)

   - Manages user interface elements like text, buttons, and menus
   - Provides functions for rendering text with different fonts
   - Example: `UI_RenderText()` draws text at a specified position on screen

**For Beginners:**
Think of Core modules as the fundamental tools that every other part of the game uses - like the hammer, nails, and measuring tape that carpenters use to build a house.

### Game Modules

Game modules implement the actual gameplay mechanics, entities, and rules.

**Key Components:**

1. **Player System** (`include/Game/player.h`, `src/Game/player.c`)

   - Manages the player character's state, movement, and abilities
   - Handles player input and collision with the environment
   - Example: `Player_InputHandler()` processes movement based on input each frame
2. **Gun System** (`include/Game/gun.h`, `src/Game/gun.c`)

   - Defines guns and their properties
   - Manages shooting mechanics, ammunition, and reloading (Though this is not implemented yet)
3. **Environment System** (`include/Game/Environment/maps.h`, `src/Game/Environment/maps.c`)

   - Defines game map generation
   - Maps are created from multiple chunks, each of which are created from multiple tiles.

**For Beginners:**
Game modules are where the actual gameplay happens - they use the Core modules as tools to create the game experience. If Core modules are like words, Game modules are the sentences and paragraphs that tell a story.

### Utilities

Utility modules provide helper functionality that doesn't fit neatly into the other categories.

**Key Components:**

1. **Animation System** (`include/Utilities/animation.h`, `src/Utilities/animation.c`)

   - Manages sprite animations and transitions
   - Tracks animation frames and timing
   - Example: `Animation_Create()` is used to create an animation, and `Animation_Render` is used to render it.
2. **Particle System** (`include/Utilities/Particles/*.h`, `src/Utilities/Particles/*.c`)

   - Provides visual effects like explosions, smoke, bullets, etc.
   - Includes particle emitters, movement patterns, and presets
   - Example: `Particles_CreateEmitterFromPreset()` generates a new particle emitter based on a particle emitter preset.
3. **Debug Utilities** (`include/Utilities/debug.h`, `src/Utilities/debug.c`)

   - Tools for debugging and diagnostics
   - Includes functions for logging, drawing debug shapes, etc.
   - Example: `Debug_RenderHitboxes()` draws hitboxes on the screen for debugging.
4. **SDL Initialization** (`include/Utilities/initialize_SDL.h`, `src/Utilities/initialize_SDL.c`)

   - Handles the setup and initialization of SDL libraries
   - Centralizes error handling for SDL initialization
   - Example: `Initialize_SDL()` sets up SDL, SDL_image, SDL_ttf, etc.
5. **Random Number Generation** (`include/Utilities/random.h`, `src/Utilities/random.c`)

   - Provides better random number generation than standard C functions
   - Used for gameplay elements requiring randomness
   - Example: `Random_Float()` generates a random floating point number in a range
6. **Timer Utilities** (`include/Utilities/timer.h`, `src/Utilities/timer.c`)

   - Manages gameplay timers for events, cooldowns, etc.
   - Different from the core Time System which handles frame timing
   - Example: `Timer_Create()` creates a new timer for tracking elapsed time

**For Beginners:**
Utility modules are like the toolbox that contains specialized tools for specific tasks - not used all the time but essential when you need them.

## Key C Concepts Used in This Project

### Pointers and Memory Management

***Pointers are variables that store memory addresses***. In this codebase, you'll see them used extensively.

For example, in the codebase, the logic to switch between guns looks something like this:

```c
GunData* currentGun = &Gun_Pistol;  
```

With:

- The currentGun variable being defined as a pointer to a GunData struct. Or in other words, it ***holds the address of a GunData struct***.
- Afterwards, the value inside the currenGun variable is set to "The address of" (&) the Gun_Pistol variable.

We use pointers to:

1. Pass large structures efficiently (without copying them)
2. Modify data across functions
3. Create dynamic data structures

### Structures

Structures group related variables under one name. This is the closest we can ever get to OOP in C. (We should have used C++)

In the codebase, you will see that we spam this everywhere we can. This is to make sure that all of our variables are organized.

```c
// Inside include/Game/player.h

typedef struct {
    // Some other states...
    GunData* currentGun;
} PlayerState;

typedef struct {
    // Some other stuffs...
    PlayerState state;
} PlayerData;
```

What's better, a struct variable can be declared as **extern** to act as global variables that are shared across the codebase.

```c
// include/Game/player.h
extern PlayerData player;

// include/App/app.h
extern AppData app;

// include/Game/Environment/maps.h
extern EnvironmentMap testMap;

// And many more!
```

## How to install & compile for Windows

### Step 1: Clone repository

You can either go File -> Download .zip to download the repository. Otherwise if you have Git, you can enter this command:
``git clone https://github.com/mangathemango/Operation-Null-Mind/``

### Step 2: Install cmake and MingW.

These should be available with a Google search. Afterwards, you can run `cmake --version` and `gcc --version` to verify.

**Note**:

**For beginners**:

- **CMake** is a build system generator that creates build files for your platform
- **MinGW** provides a Windows version of the GCC compiler and necessary tools

### Step 3: Build, Compile and Run

To build, there are 2 ways you can do this

If you have vscode, just `Ctrl+Shift+B`. It should all run fine.

Otherwise, you can run these 3 commands:

```
cmake -S . -B build "MinGW Makefiles"
cmake --build build
```

Right now, the .exe file should be inside the `build/` folder, which you can run straight away

```
./build/Operation-Null-Mind
```

#### Note:

Sometimes github does a weird thingy where the .c files turn into .C, which, automatically detects it as a C++ file instead of C @v@ goofy ah.

In that case, you can enter this command into terminal:

```
Get-ChildItem -Path .\src -Filter *.C -Recurse | Rename-Item -NewName {$_.name -replace '\.C$','.c'}
```
