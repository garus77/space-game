cmake_minimum_required(VERSION 3.16)
project(Galaxus)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include our headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Find all .cpp files under src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

# Debug output
message(STATUS "Project source files: ${SOURCES}")

# Now actually make the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link SFML (installed under MSYS2 UCRT64)
find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-audio)
