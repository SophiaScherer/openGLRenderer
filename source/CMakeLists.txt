project(GraphicsRenderer)

include(FetchContent)

set(BUILD_SHARED_LIBS ON)

add_library(${PROJECT_NAME}
    ../external/include/glad/glad.c
    GraphicsRenderer.cpp
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