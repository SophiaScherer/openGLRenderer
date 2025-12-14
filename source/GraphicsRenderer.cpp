#include "GraphicsRenderer.h"
#include <iostream>
#include <stdexcept>

namespace gr
{
  GraphicsRenderer::GraphicsRenderer(int width, int height, const std::string& title)
    : width(width), height(height), title(title), window(nullptr)
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
  }

  void GraphicsRenderer::run() const
  {
    while (!glfwWindowShouldClose(window))
    {
      glClear(GL_COLOR_BUFFER_BIT);

      glfwSwapBuffers(window);

      glfwPollEvents();
    }
  }

  void GraphicsRenderer::cleanUp()
  {
    glfwTerminate();
  }
}