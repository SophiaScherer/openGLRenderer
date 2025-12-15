#include <glad/glad.h>
#include "GraphicsRenderer.h"
#include "Shader.h"
#include <stdexcept>
#include <utility>

namespace gr
{
  GraphicsRenderer::GraphicsRenderer(const int width, const int height, std::string  title)
    : window(nullptr), width(width), height(height), title(std::move(title))
  {
    initWindow();
  }

  GraphicsRenderer::~GraphicsRenderer()
  {
    cleanUp();
  }

  void GraphicsRenderer::initWindow()
  {
    if (!glfwInit())
    {
      throw std::runtime_error("Failed to initialize GLFW");
    }

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!window)
    {
      glfwTerminate();
      throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
      throw std::runtime_error("Failed to initialize GLAD");
    }
  }

  bool GraphicsRenderer::isAlive() const
  {
    return !glfwWindowShouldClose(window);
  }

  void GraphicsRenderer::run() const
  {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  void GraphicsRenderer::cleanUp()
  {
    glfwTerminate();
  }
}
