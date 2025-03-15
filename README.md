# Operation Null Mind

## Table of Contents
- [How to Run the Game](#how-to-run-the-game)
- [Controls](#controls)
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
  - [[Utilities]](#utilities)
  - [[?]](#)
- [Key C Concepts Used in This Project](#key-c-concepts-used-in-this-project)
  - [Pointers and Memory Management](#pointers-and-memory-management)
  - [Structures](#structures)
- [How to Install & Compile for Windows](#how-to-install--compile-for-windows)
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

## Key C Concepts Used in This Project

### Pointers and Memory Management
***Pointers are variables that store memory addresses***. In this codebase, you'll see them used extensively.

For example, in the codebase, the logic to switch between guns looks something like this:
```c
GunData* currentGun = &Gun_Pistol;  
```
With: 
-   The currentGun variable being defined as a pointer to a GunData struct. Or in other words, it ***holds the address of a GunData struct***.
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