cmake_minimum_required(VERSION 3.16)
project(Galaxus VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# — Put the executable into build/bin —
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# — Copy settings.json next to the binary —
configure_file(
    ${CMAKE_SOURCE_DIR}/settings.json
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/settings.json
    COPYONLY
)

# — Define the executable and its include path —
add_executable(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

# — Gather all your .cpp sources —
file(GLOB_RECURSE SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/source/*.cpp
)
target_sources(${PROJECT_NAME}
    PRIVATE
        ${SOURCES}
)

# — Use CMake’s built-in FindSFML module (not the SFMLConfig export) —
find_package(SFML 2.6 REQUIRED COMPONENTS
    graphics
    window
    system
    audio
)

# — Link against the plain sfml-<component> libraries —
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
)