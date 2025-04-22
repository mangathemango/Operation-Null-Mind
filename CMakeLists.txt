cmake_minimum_required(VERSION 3.10)
project(Operation-Null-Mind VERSION 1.0)

# Set compiler flags
add_compile_options(-Wall)


# Include directories
include_directories(src)

# Add library directory
link_directories(lib)

# Include all directories in include folder
include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE INCLUDE_DIRS LIST_DIRECTORIES true "${CMAKE_SOURCE_DIR}/include/*")
foreach(DIR ${INCLUDE_DIRS})
    if(IS_DIRECTORY ${DIR})
    include_directories(${DIR})
    endif()
endforeach()

# Include Asses folder
include_directories(Assets)

# Find all source files in src directory
file(GLOB_RECURSE SOURCES "src/*.c")
set_source_files_properties(${SOURCES} PROPERTIES LANGUAGE C)

# Create executable
add_executable(Operation-Null-Mind ${SOURCES})

# Find all DLLs in lib folder and copy them
file(COPY ${CMAKE_SOURCE_DIR}/bin/ DESTINATION ${CMAKE_BINARY_DIR} FILES_MATCHING PATTERN "*.dll")
file(COPY ${CMAKE_SOURCE_DIR}/Assets/ DESTINATION ${CMAKE_BINARY_DIR}/Assets)


# Link libraries
target_link_libraries(Operation-Null-Mind
    mingw32
    SDL2main
    SDL2
    SDL2_image
    SDL2_mixer
    SDL2_ttf
    -mwindows
)