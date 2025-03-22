\mainpage Operation Null Mind

\tableofcontents

\section controls Controls
- WASD - Move character
- Left click - Shoot
- 1 2 3 4 5 - Switch weapons (for now)
- Shift - Skill 1 (Dash)

\section running How to Run the Game
If the zip file has a build foler, just click on build/Operation-Null-Mind.exe

\section about About the Codebase
Most of everything (around 90%) inside the codebase is already pretty well documented. But generally, if you want to look around on how everything works, you should start on src/main.c (which contains the game loop), then everything inside include/app.h and the folder src/App/, then everything else inbetween.

\subsection structure Code Structure
This project follows a modular structure to keep the code organized:

\code{.txt}
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
\endcode

\subsection flow Understanding the Code Flow
The game follows this general flow:

1. **Initialization**: Set up SDL, load resources, initialize game state. This is done inside the App_Start() function.
2. **Game Loop**: Process events, update game state, render graphics. This is done inside the App_PreUpdate(), App_Event_Handler(), App_PostUpdate(), and App_Render().
3. **Cleanup**: Free resources and shut down the program. This is done inside the App_Quit().

\section naming Function Naming Convention
All of our functions are labelled with tags that indicate when they are called in the game lifecycle:

\subsection start [Start]
These functions are called once at the start of the program, used for data initialization and the like. Every [Start] functions should be called somewhere inside app_start.c

**Example**: \c Player_Start() initializes the player's health, position, and abilities.

\subsection preupdate [PreUpdate]
These functions are called ***every frame*** before everything else. This is mainly functions used as a SETUP for the current frame, rather than handling the main logic. This includes resetting some booleans, positions, etc.

**Example**: \c Input_PreUpdate() resets input states at the beginning of each frame.

\subsection eventhandler [Event_Handler]
Event_Handler are called ***every frame*** whenever there's an event detected, like mouse click, key board press, etc.

**For beginners**: Think of events as signals that something happened (like a key press). The event handler catches these signals and updates our game accordingly.

*Right now, App_Event_handler is only used to quit the program and update our Input struct inside Core/input.c. The Input struct tells you everything about what's going on with the keyboard and mouse - whether a button was just pressed/released, or whether it is being held. This allows for more flexible event handling - without having to pass the SDL_Event struct on all the functions that requires player input.*

\subsection postupdate [PostUpdate]
These functions are called every frame to handle the main logic of the frame - for example updating player's position, gun rotation, input handling, etc.

**Example**: \c Player_PostUpdate() updates the player's position based on input and handles collisions.

\subsection render [Render]
Well, those functions are called every frame just to render stuff. Quite simple.

**Example**: \c Player_Render() draws the player character at its current position.

\subsection quit [Quit]
And these functions, well, is called at the end of the program. This mostly includes functions that free up memory of something (though we havent worked on that yet)

**For beginners**: In C, you need to manually free memory that you've allocated. These functions make sure we don't have memory leaks.

\subsection utilities [Utilities]
These functions are called basically anywhere - and acts as a helper function for other functions.

**Example**: \c Vec2_Distance() calculates the distance between two points.

\subsection conditional [?]
Some tags have this ? thing (like [PostUpdate?]), which says that they are called every frame only if a certain condition are met.

\section modules Key Modules Overview
This section provides an overview of the main modules that make up the game. Understanding these key components will help you navigate the codebase more effectively.

\subsection app App Module
The App module is the core orchestrator of the game. It manages the game lifecycle and ties all other modules together.

**Key Files:**

- \c include/App/app.h - Main application header defining the AppData structure and function prototypes
- \c src/App/app_start.c - Initialization logic that runs once at startup
- \c src/App/app_preupdate.c - Frame setup logic that runs before processing game logic
- \c src/App/app_event_handler.c - Handles SDL events like keyboard/mouse input
- \c src/App/app_postupdate.c - Main game logic that runs each frame
- \c src/App/app_render.c - Rendering logic that draws everything to the screen
- \c src/App/app_quit.c - Cleanup logic that runs when the game exits

**For Beginners:**
The App module is like the conductor of an orchestra - it doesn't make music itself, but it coordinates all the other modules to work together.

\subsection core Core Modules
Core modules provide fundamental functionality that the rest of the game relies on. They handle basic operations like math, input, and rendering.

**Key Components:**

1. **Vector System** (\c include/Core/vec2.h, \c src/Core/vec2.c)

   - Provides 2D vector operations like addition, subtraction, normalization
   - Used for positions, movement, and direction calculations
   - Example: \c Vec2_Add() combines two vectors, useful for adding velocity to position
2. **Input System** (\c include/Core/input.h, \c src/Core/input.c)

   - Tracks keyboard and mouse state
   - Distinguishes between keys just pressed, held down, or just released
   - Example: \c Input->mouse.leftButton.pressed is true on the first frame the left mouse button is pressed
3. **Time System** (\c include/Core/time.h, \c src/Core/time.c)

   - Manages game timing, delta time, and frame rate
   - Ensures consistent game speed regardless of frame rate
   - Example: \c Time->deltaTimeSeconds returns the time elapsed since the last frame
4. **Camera System** (\c include/Core/camera.h, \c src/Core/camera.c)

   - Handles viewport and screen-to-world coordinate transformations
   - Manages camera movement, zoom, and following objects
   - Example: \c Camera_WorldToScreen() converts world coordinates to screen coordinates
5. **Colliders System** (\c include/Core/colliders.h, \c src/Core/colliders.c)

   - Provides collision detection between game entities
   - Supports different collider shapes (rectangles, circles)
   - Example: \c Collider_CheckRectRect() tests if two rectangle colliders intersect
6. **Sound System** (\c include/Core/sound.h, \c src/Core/sound.c)

   - Manages audio playback for music and sound effects
   - Handles loading, playing, and stopping audio files
   - Example: \c Sound_PlaySFX() plays a sound effect with optional volume control
7. **UI System** (\c include/Core/UI/UI_text.h, \c src/Core/UI/UI_text.c)

   - Manages user interface elements like text, buttons, and menus
   - Provides functions for rendering text with different fonts
   - Example: \c UI_RenderText() draws text at a specified position on screen

**For Beginners:**
Think of Core modules as the fundamental tools that every other part of the game uses - like the hammer, nails, and measuring tape that carpenters use to build a house.

\subsection game Game Modules
Game modules implement the actual gameplay mechanics, entities, and rules.

**Key Components:**

1. **Player System** (\c include/Game/player.h, \c src/Game/player.c)

   - Manages the player character's state, movement, and abilities
   - Handles player input and collision with the environment
   - Example: \c Player_InputHandler() processes movement based on input each frame
2. **Gun System** (\c include/Game/gun.h, \c src/Game/gun.c)

   - Defines guns and their properties
   - Manages shooting mechanics, ammunition, and reloading (Though this is not implemented yet)
3. **Environment System** (\c include/Game/Environment/maps.h, \c src/Game/Environment/maps.c)

   - Defines game map generation
   - Maps are created from multiple chunks, each of which are created from multiple tiles.

**For Beginners:**
Game modules are where the actual gameplay happens - they use the Core modules as tools to create the game experience. If Core modules are like words, Game modules are the sentences and paragraphs that tell a story.

\subsection util Utilities
Utility modules provide helper functionality that doesn't fit neatly into the other categories.

**Key Components:**

1. **Animation System** (\c include/Utilities/animation.h, \c src/Utilities/animation.c)

   - Manages sprite animations and transitions
   - Tracks animation frames and timing
   - Example: \c Animation_Create() is used to create an animation, and \c Animation_Render is used to render it.
2. **Particle System** (\c include/Utilities/Particles/*.h, \c src/Utilities/Particles/*.c)

   - Provides visual effects like explosions, smoke, bullets, etc.
   - Includes particle emitters, movement patterns, and presets
   - Example: \c Particles_CreateEmitterFromPreset() generates a new particle emitter based on a particle emitter preset.
3. **Debug Utilities** (\c include/Utilities/debug.h, \c src/Utilities/debug.c)

   - Tools for debugging and diagnostics
   - Includes functions for logging, drawing debug shapes, etc.
   - Example: \c Debug_RenderHitboxes() draws hitboxes on the screen for debugging.
4. **SDL Initialization** (\c include/Utilities/initialize_SDL.h, \c src/Utilities/initialize_SDL.c)

   - Handles the setup and initialization of SDL libraries
   - Centralizes error handling for SDL initialization
   - Example: \c Initialize_SDL() sets up SDL, SDL_image, SDL_ttf, etc.
5. **Random Number Generation** (\c include/Utilities/random.h, \c src/Utilities/random.c)

   - Provides better random number generation than standard C functions
   - Used for gameplay elements requiring randomness
   - Example: \c Random_Float() generates a random floating point number in a range
6. **Timer Utilities** (\c include/Utilities/timer.h, \c src/Utilities/timer.c)

   - Manages gameplay timers for events, cooldowns, etc.
   - Different from the core Time System which handles frame timing
   - Example: \c Timer_Create() creates a new timer for tracking elapsed time

**For Beginners:**
Utility modules are like the toolbox that contains specialized tools for specific tasks - not used all the time but essential when you need them.

\section concepts Key C Concepts Used in This Project

\subsection pointers Pointers and Memory Management
***Pointers are variables that store memory addresses***. In this codebase, you'll see them used extensively.

For example, in the codebase, the logic to switch between guns looks something like this:

\code{.c}
GunData* currentGun = &Gun_Pistol;  
\endcode

With:

- The currentGun variable being defined as a pointer to a GunData struct. Or in other words, it ***holds the address of a GunData struct***.
- Afterwards, the value inside the currenGun variable is set to "The address of" (&) the Gun_Pistol variable.

We use pointers to:

1. Pass large structures efficiently (without copying them)
2. Modify data across functions
3. Create dynamic data structures

\subsection structures Structures
Structures group related variables under one name. This is the closest we can ever get to OOP in C. (We should have used C++)

In the codebase, you will see that we spam this everywhere we can. This is to make sure that all of our variables are organized.

\code{.c}
// Inside include/Game/player.h

typedef struct {
    // Some other states...
    GunData* currentGun;
} PlayerState;

typedef struct {
    // Some other stuffs...
    PlayerState state;
} PlayerData;
\endcode

What's better, a struct variable can be declared as **extern** to act as global variables that are shared across the codebase.

\code{.c}
// include/Game/player.h
extern PlayerData player;

// include/App/app.h
extern AppData app;

// include/Game/Environment/maps.h
extern EnvironmentMap testMap;

// And many more!
\endcode

\section installation How to Install & Compile for Windows

\subsection clone Step 1: Clone repository
You can either go File -> Download .zip to download the repository. Otherwise if you have Git, you can enter this command:
\code{.bash}
git clone https://github.com/mangathemango/Operation-Null-Mind/
\endcode

\subsection dependencies Step 2: Install cmake and MingW
These should be available with a Google search. Afterwards, you can run \c cmake --version and \c gcc --version to verify.

**Note**:

**For beginners**:

- **CMake** is a build system generator that creates build files for your platform
- **MinGW** provides a Windows version of the GCC compiler and necessary tools

\subsection build Step 3: Build, Compile and Run
To build, there are 2 ways you can do this

If you have vscode, just \c Ctrl+Shift+B. It should all run fine.

Otherwise, you can run these 3 commands:

\code{.bash}
cmake -S . -B build "MinGW Makefiles"
cmake --build build
\endcode

Right now, the .exe file should be inside the \c build/ folder, which you can run straight away

\code{.bash}
./build/Operation-Null-Mind
\endcode

\subsection note Note
Sometimes github does a weird thingy where the .c files turn into .C, which, automatically detects it as a C++ file instead of C @v@ goofy ah.

In that case, you can enter this command into terminal:

\code{.powershell}
Get-ChildItem -Path .\src -Filter *.C -Recurse | Rename-Item -NewName {$_.name -replace '\.C$','.c'}
\endcode
