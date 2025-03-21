\mainpage Operation Null Mind

\section intro Introduction
EVERYTHING HERE IS WRITTEN BY AI BTW SO IT'S NOT FACTUALLY CORRECT
**Operation Null Mind** is a 2D roguelike top-down shooter game developed using SDL2. Set in a dystopian future, players navigate through procedurally generated environments, battling against hostile forces while uncovering the mysteries of a world where consciousness has been weaponized. The game blends fast-paced action with strategic roguelike elements to create a unique gameplay experience.

\section overview Game Overview
In Operation Null Mind, players take control of a protagonist fighting through a series of challenging levels. Each playthrough offers:
- Unique level layouts through procedural generation
- Permanent character progression between runs
- Diverse combat scenarios requiring tactical thinking
- Resource management and decision-making elements
- An evolving narrative revealed through gameplay

\section features Key Features
\subsection mapgen Advanced Procedural Generation
- Multi-layered map generation algorithm that creates varied, balanced environments
- Main path system ensuring proper game flow and progression
- Room variety including combat arenas, treasure rooms, and special encounters
- Quadrant-based level design with increasing difficulty toward the end room
- Procedural decoration and object placement

\subsection combat Combat System
- Responsive twin-stick style shooting mechanics
- Diverse weapon types with unique properties and behaviors
- Projectile physics including collision, penetration, and area effects
- Dynamic enemy encounters with varying difficulty
- Special abilities and power-ups that modify gameplay

\subsection progression Progression System
- Permanent character upgrades between runs
- Temporary power-ups during individual playthroughs
- Unlockable weapons and abilities
- Achievement and challenge systems
- Dynamic difficulty scaling based on player performance

\subsection ai Enemy AI
- Multiple enemy types with distinct behavior patterns
- State-based AI decision making
- Path-finding algorithms for intelligent movement
- Target prioritization and threat assessment
- Squad-based coordinated attacks for advanced enemies

\section technical Technical Architecture
The game is built with a modular, component-based architecture that separates concerns into distinct systems:

\subsection app Application Framework
The core application layer manages the game window, rendering context, and the main game loop. It handles scene transitions, input processing, and maintains the application state.

```cpp
// From app_data.c
AppData app = {
    .resources = {
        .window = NULL,
        .renderer = NULL,
        .screenTexture = NULL,
    },
    .state = {
        .running = true,
        .fps = 0,
        .averageFps = 0,
        .currentScene = SCENE_MENU,
    },
    .config = {
        .window_title = "Operation Null Mind",
        .window_width = 1024,
        .window_height = 768,
        .window_fullscreen = false,
        .screen_width = 480,
        .screen_height = 288,
        .debug = false,
        .title1FontPath = "Assets/Fonts/Bore Blasters 16.ttf",
        .title2FontPath = "Assets/Fonts/Bore Blasters 16.ttf",
        .textFontPath = "Assets/Fonts/monogram.ttf",
    },
};
```

\subsection scene Scene Management
The game implements a scene-based architecture where different game states (menu, gameplay, pause, etc.) are encapsulated in scene objects with their own update and render methods.

\subsection maps Map Generation System
The procedural map generation system creates unique, playable levels for each run. It follows a multi-stage process:

1. **Chunk Division**: Divides the map into chunks of equal size
2. **Main Path Creation**: Generates the primary path from start to end
3. **Side Area Generation**: Creates optional exploration areas
4. **Room Placement**: Places different room types based on location and context
5. **Detail Generation**: Adds details, obstacles, and decorative elements

```cpp
// Map generation example from map_create.c
Map_CreateMainPath();
    
// Place end room (always in bottom-right quadrant)
Map_SetEndChunk(testMap.mainPath[testMap.mainPathLength].x, testMap.mainPath[testMap.mainPathLength].y);
SDL_Log("Current position: (%d, %d) - Target position: (%d, %d)\n", startX, startY,
        (int) testMap.mainPath[testMap.mainPathLength].x, (int) testMap.mainPath[testMap.mainPathLength].y);

// Process main path points
for(int k = 0; k < MAP_LENGTH + 1; k++) {
    SDL_Log("Main Path: (%d, %d)", (int) testMap.mainPath[k].x, (int) testMap.mainPath[k].y);
}

// Initialize all non-empty chunks
for (int x = 0; x < MAP_SIZE_CHUNK; x++) {
    for (int y = 0; y < MAP_SIZE_CHUNK; y++) {
        if (!testMap.chunks[x][y].empty) {
            // Initialize chunk contents
        }
    }
}
```

\subsection entities Entity Component System
The game uses a flexible entity component system (ECS) to manage all game objects:

\subsubsection player Player Entity
- Health and shield management
- Movement controller
- Weapon and inventory systems
- Ability and skill handlers
- Camera follow system
- Input interpretation

\subsubsection enemies Enemy Entities
- Various enemy types with different behaviors
- Health and damage systems
- AI controllers
- Animation state machines
- Specialized attack patterns
- Spawn and despawn management

\subsubsection weapons Weapons and Projectiles
- Multiple weapon types (melee, ranged, special)
- Projectile physics and collision detection
- Area-of-effect capabilities
- Status effect application
- Visual and audio feedback

\subsubsection items Items and Pickups
- Health and shield pickups
- Ammunition and resources
- Temporary and permanent power-ups
- Special ability unlocks
- Currency and collectibles

\subsection collision Collision System
A sophisticated collision detection and resolution system that handles:
- Entity-entity interactions
- Entity-environment interactions
- Projectile collisions
- Trigger zones and area effects
- Spatial partitioning for performance optimization

\subsection rendering Rendering Pipeline
The game employs a multi-layered rendering system using SDL2:

\subsubsection sprites Sprite Rendering
- Texture loading and management
- Sprite animation system
- Dynamic texture manipulation
- Parallax background effects
- Sprite batching for performance

\subsubsection lighting Lighting and Effects
- Dynamic lighting system
- Particle effects for impacts, explosions, and environmental details
- Screen shaders for special effects
- Post-processing effects
- Camera effects (shake, zoom, etc.)

\subsubsection ui User Interface
- In-game HUD with health, ammo, and status indicators
- Menu systems with controller and keyboard navigation
- Inventory and ability selection interfaces
- Dialog and narrative presentation
- Feedback systems for player actions

\subsection audio Audio System
A comprehensive audio management system with:
- Dynamic sound effects based on game events
- Adaptive music that responds to gameplay intensity
- Spatial audio for immersive experiences
- Volume management and audio settings
- Voice and narrative audio

\section implementation Implementation Details

\subsection sdl2 SDL2 Integration
The game leverages multiple SDL2 libraries:
- **SDL2 Core**: Window management, rendering, and input handling
- **SDL2_image**: Texture loading with support for multiple formats
- **SDL2_ttf**: Text rendering for UI elements
- **SDL2_mixer**: Audio playback and management

\subsection optimization Performance Optimization
Several techniques are employed to ensure smooth gameplay:
- Spatial partitioning for collision detection
- Object pooling for frequently used entities
- Texture atlasing to minimize draw calls
- Frustum culling to avoid rendering off-screen elements
- Memory management to reduce garbage collection

\subsection patterns Design Patterns
The codebase utilizes several design patterns:
- **State Pattern**: For entity behavior and game state management
- **Observer Pattern**: For event handling and system communication
- **Factory Pattern**: For entity creation and management
- **Component Pattern**: For modular entity composition
- **Singleton Pattern**: For global system access

\section building Building and Running
\subsection prerequisites Prerequisites
To build and run Operation Null Mind, you'll need:
- A C compiler (GCC, Clang, or MSVC)
- SDL2 development libraries (core, image, ttf, mixer)
- CMake or Make build system
- Git for version control

\subsection steps Build Steps
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/operation-null-mind.git
   cd operation-null-mind
   ```

2. Install dependencies:
   - **Windows**: Download SDL2 development libraries and place in the appropriate directories
   - **Linux**: `sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev`
   - **macOS**: `brew install sdl2 sdl2_image sdl2_ttf sdl2_mixer`

3. Build the project:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

4. Run the executable:
   ```bash
   ./operation-null-mind
   ```

\subsection config Configuration
The game can be configured through several methods:
- Editing the configuration values in app_data.c before compilation
- Using command-line arguments when launching the game
- Modifying settings through the in-game options menu
- Creating a custom configuration file (format specified in documentation)

\section development Development Information
\subsection codeorg Code Organization
The project follows a structured organization:
- **src/App**: Core application framework
- **src/Game**: Main gameplay systems
- **src/Game/Environment**: Map and level systems
- **src/Game/Entities**: Entity implementations
- **src/Render**: Rendering systems
- **src/UI**: User interface components
- **src/Audio**: Sound and music systems
- **src/Utils**: Utility functions and helpers

\subsection contributing Contributing
Contributions to Operation Null Mind are welcome! To contribute:
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

Please follow the coding standards outlined in the CONTRIBUTING.md file.

\subsection testing Testing
The project uses several testing approaches:
- Unit tests for core functionality
- Integration tests for system interactions
- Playtest sessions for gameplay balance and feel
- Performance testing to identify bottlenecks

\section roadmap Development Roadmap
Future development plans include:
- Additional enemy types and behaviors
- New weapon categories and special abilities
- Enhanced procedural generation algorithms
- Multiplayer cooperative mode
- Console platform support

\section license License
Operation Null Mind is released under the [insert your license here] license. See the LICENSE file for complete details.

\section acknowledgments Acknowledgments
Special thanks to:
- The SDL2 development team
- Contributors and playtesters
- [Any other acknowledgments you want to include]
