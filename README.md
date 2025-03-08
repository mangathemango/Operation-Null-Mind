# Operation Null Mind

## How to run the game:

Pretty easy, just click on build/Operation-Null-Mind.exe

## Controls:

WASD - Move character

Left click - Shoot

1 2 3 4 5 -  Switch weapons (for now)

Shift  - Skill 1 (Dash)

## About the codebase:

Most of everything (around 90%) inside the codebase is already pretty well documented. But generally, if you want to look around on how everything works, you should start on src/main.c (which contains the game loop), then everything inside include/app.h and the folder src/App/, then everything else inbetween.

All of our functions are labelled as follows (even though we may have missed some):

### [Start]

These functions are called once at the start of the program, used for data initialization and the like. Every [Start] functions should be called somewhere inside app_start.c

### [PreUpdate]

These functions are called ***every frame*** before everything else. This is mainly functions used as a SETUP for the current frame, rather than handling the main logic. This includes resetting some booleans, positions, etc.

### [Event_Handler]

Event_Handler are called ***every frame*** whenever there's an event detected, like mouse click, key board press, etc.

Right now, App_Event_handler is only used to quit the program and update our Input struct inside Core/input.c. The Input struct tells you everything about what's going on with the keyboard and mouse - whether a button was just pressed/released, or whether it is being held. This allows for more flexible event handling - without having to pass the SDL_Event struct on all the functions that requires player input.

### [PostUpdate]

These functions are called every frame to handle the main logic of the frame - for example updating player's position, gun rotation, input handling, etc.

### [Render]

Well, those functions are called every frame just to render stuff. Quite simple.

### [Quit]

And these functions, well, is called at the end of the program. This mostly includes functions that free up memory of something (though we havent worked on that yet)

### [Utilities]

These functions are called basically anywhere - and acts as a helper function for other functions.

### [?]

Some tags have this ? thing (like [PostUpdate?]), which says that they are called every frame only if a certain condition are met.

## By the way

The physical collision system is being worked on and is semi working right now! You can check out the branch tony_wall_collision for more info

## How to install & compile for Windows

### Step 1: Clone repository

You can either go File -> Download .zip to download the repository. Otherwise if you have Git, you can enter this command:
``git clone https://github.com/mangathemango/Operation-Null-Mind/``

### Step 2: Install cmake and MingW.

These should be available with a Google search. Afterwards, you can run `cmake --version` and `gcc --version` to verify.

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
./build/Operation-Ruinam-Dei
```

#### Note:

Sometimes github does a weird thingy where the .c files turn into .C, which, automatically detects it as a C++ file instead of C @v@ goofy ah.

In that case, you can enter this command into terminal:

```
Get-ChildItem -Path .\src -Filter *.C -Recurse | Rename-Item -NewName {$_.name -replace '\.C$','.c'}
```
