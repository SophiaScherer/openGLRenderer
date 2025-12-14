#include "GraphicsRenderer.h"
#include <iostream>
#include <stdexcept>

namespace gr
{

  GraphicsRenderer::GraphicsRenderer()
  {
    if (!glfwInit())
    {
      throw std::runtime_error("Failed to initialize GLFW");
    }

    window = glfwCreateWindow(640, 480, "Hello World!", NULL, NULL);

    if (!window)
    {
      glfwTerminate();
      throw std::runtime_error("Failed to create GLFW window");
    }
  }
}
