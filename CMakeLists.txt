cmake_minimum_required(VERSION 3.10)
project(OpenGLProject)

# Définir le standard C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Configuration macOS et Homebrew
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
    
    # Ajout du chemin correct pour SFML
    set(SFML_DIR "/opt/homebrew/Cellar/sfml@2/2.6.2/lib/cmake/SFML")
    
    # Ajout des chemins d'inclusion Homebrew
    include_directories("/opt/homebrew/include")
    link_directories("/opt/homebrew/lib")
endif()

# Automatically find all source files
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/*.c"
)

# Automatically find all header files
file(GLOB_RECURSE HEADERS
    "include/*.hpp"
    "include/*.h"
)

# Find SFML
find_package(SFML 2.6.2 COMPONENTS graphics window system REQUIRED)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)