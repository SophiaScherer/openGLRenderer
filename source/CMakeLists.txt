project(GraphicsRenderer)

include(FetchContent)

set(BUILD_SHARED_LIBS ON)

add_library(${PROJECT_NAME}
    ../external/include/glad/glad.c
    GraphicsRenderer.cpp
    Shader.cpp
    Window.cpp
    ShaderManager.cpp
    ShapeDrawer.cpp
)

# GLFW
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

# GLM
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.2
)

FetchContent_MakeAvailable(
    glfw
    glm
)

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC
    glfw
    OpenGL::GL
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${glm_SOURCE_DIR}
    ../external/include
)

function(copy_shaders)
    set(shadersSrc ${CMAKE_CURRENT_SOURCE_DIR}/shaders)
    set(shadersDst ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders)

    file(MAKE_DIRECTORY ${shadersDst})

    # Find all shader files
    file(GLOB_RECURSE SHADER_FILES
            "${shadersSrc}/*.vert"
            "${shadersSrc}/*.frag"
            "${shadersSrc}/*.geom"
            "${shadersSrc}/*.glsl"
    )

    set(COPIED_SHADERS "")

    foreach(SHADER ${SHADER_FILES})
        # Get the relative path and filename
        file(RELATIVE_PATH REL_PATH ${shadersSrc} ${SHADER})
        get_filename_component(FILENAME ${SHADER} NAME)

        # Set the output path
        set(OUTPUT_FILE "${shadersDst}/${FILENAME}")

        # Append to list
        list(APPEND COPIED_SHADERS ${OUTPUT_FILE})

        # Add custom command to copy shader
        add_custom_command(
                OUTPUT ${OUTPUT_FILE}
                COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SHADER} ${OUTPUT_FILE}
                DEPENDS ${SHADER}
                COMMENT "Copying shader: ${REL_PATH}"
        )
    endforeach()

    # Create custom target
    add_custom_target(CopyShaders ALL DEPENDS ${COPIED_SHADERS})
endfunction()

# Call the function
copy_shaders()

# Add dependency so shaders are copied before building
add_dependencies(${PROJECT_NAME} CopyShaders)