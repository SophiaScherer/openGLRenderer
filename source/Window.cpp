#include <glad/glad.h>
#include "Window.h"
#include <iostream>

namespace gr {

  Window::Window(const int width, const int height, const std::string title)
  : m_width(width), m_height(height), m_title(title)
  {
    initGLFW();
    createWindow();
    initGLAD();
  }

  Window::~Window()
  {
    glfwTerminate();
  }

  void Window::initGLFW()
  {
    if (!glfwInit())
    {
      throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  }

  void Window::createWindow()
  {
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

    if (!m_window)
    {
      glfwTerminate();
      throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(m_window);
  }

  void Window::initGLAD()
  {
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
      throw std::runtime_error("Failed to initialize GLAD");
    }

    glViewport(0, 0, m_width, m_height);
  }

}