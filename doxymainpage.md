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



