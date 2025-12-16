#include <glad/glad.h>
#include "GraphicsRenderer.h"
#include "Shader.h"
#include <stdexcept>
#include <utility>

#include "glm/ext/matrix_clip_space.hpp"

namespace gr
{
  GraphicsRenderer::GraphicsRenderer(const int width, const int height, std::string  title)
    : window(nullptr), width(width), height(height), title(std::move(title))
  {
    initWindow();
    initOpenGL();
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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    glViewport(0, 0, width, height);
  }

  void GraphicsRenderer::initOpenGL()
  {
    shader = std::make_unique<Shader>("shaders/shape.vert", "shaders/shape.frag");
    ellipseShader = std::make_unique<Shader>("shaders/ellipse.vert", "shaders/ellipse.frag");

    projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);
    //
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  bool GraphicsRenderer::isAlive() const
  {
    return !glfwWindowShouldClose(window);
  }

  void GraphicsRenderer::clear() const
  {
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void GraphicsRenderer::present() const
  {
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  void GraphicsRenderer::rectangle(float x, float y, float width, float height, float r, float g, float b) const
  {
    float vertices[] = {
      x, y,
      x + width, y,
      x + width, y + height,

      x + width, y + height,
      x, y + height,
      x, y
    };

    shader->use();

    shader->setUniform("color", r, g, b);
    shader->setUniform("projection", projection);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
  }

  void GraphicsRenderer::triangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b) const
  {
    float vertices[] = {
      x1, y1,
      x2, y2,
      x3, y3
    };

    shader->use();
    shader->setUniform("color", r, g, b);
    shader->setUniform("projection", projection);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
  }

  void GraphicsRenderer::ellipse(float cx, float cy, float xRad, float yRad, float r, float g, float b) const
  {
    float x = cx - xRad;
    float y = cy - yRad;
    float width = 2 * xRad;
    float height = 2 * yRad;

    float vertices[] = {
      x, y,
      x + width, y,
      x + width, y + height,
      x + width, y + height,
      x, y + height,
      x, y
    };

    ellipseShader->use();
    ellipseShader->setUniform("color", r, g, b);
    ellipseShader->setUniform("projection", projection);

    ellipseShader->setUniform("center", cx, cy);
    ellipseShader->setUniform("rad", xRad, yRad);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

    glBindVertexArray(0);
  }

  void GraphicsRenderer::cleanUp()
  {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
  }
}
