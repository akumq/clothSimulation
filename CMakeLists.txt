cmake_minimum_required(VERSION 3.10)
project(OpenGLProject)

# Configuration macOS
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
endif()

# Trouver automatiquement tous les fichiers sources
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.c"
)

# Trouver automatiquement tous les headers
file(GLOB_RECURSE HEADERS
    "include/*.hpp"
    "include/*.h"
)

# Packages
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Linking
target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system
)

target_include_directories(${PROJECT_NAME} PRIVATE include) 