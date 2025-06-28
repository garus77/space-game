cmake_minimum_required(VERSION 3.16)
project(Galaxus VERSION 0.1.1 LANGUAGES CXX)

# — Require C++17 —
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

# — Ensure icon.ico is available at configure-time for windres —
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/resources/textures)
file(COPY
    ${CMAKE_SOURCE_DIR}/resources/textures/icon.ico
    DESTINATION ${CMAKE_BINARY_DIR}/resources/textures
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

# — Embed the Windows icon via icon.rc (requires icon.ico in build/resources/textures) —
if(WIN32)
    target_sources(${PROJECT_NAME}
        PRIVATE
            ${CMAKE_SOURCE_DIR}/resources/icon.rc
    )
endif()

# — Copy entire resources/ tree (textures/, audio/) into build/bin/resources after build —
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources)
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources
    COMMENT "Copying resources (textures/, audio/) to output directory"
)

# — Find SFML via CMake’s built-in module —
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

if(WIN32)
    set(SFML_DLL_SOURCE_DIR ${CMAKE_SOURCE_DIR}/lib)

    # only in Release builds:
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        if(EXISTS "${SFML_DLL_SOURCE_DIR}")
            add_custom_command(
                TARGET ${PROJECT_NAME}
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                    "${SFML_DLL_SOURCE_DIR}"
                    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
                COMMENT "Copying SFML DLLs from ${SFML_DLL_SOURCE_DIR} to output directory"
            )
        else()
            message(WARNING "SFML DLL folder not found: ${SFML_DLL_SOURCE_DIR}")
        endif()
    endif()
endif()

if(MINGW)
  target_link_options(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:-mwindows>
  )
elseif(MSVC)
  target_link_options(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS>
  )
endif()

# — Packaging target: zip up the contents of bin/ directly —
add_custom_target(package
  COMMENT "Creating ${PROJECT_NAME}-${PROJECT_VERSION}.zip"
  COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
          ${CMAKE_COMMAND} -E tar
            cfv
            ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-v${PROJECT_VERSION}.zip
            --format=zip
            .
  DEPENDS ${PROJECT_NAME}
)