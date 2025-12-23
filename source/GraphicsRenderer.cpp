#include <glad/glad.h>
#include "GraphicsRenderer.h"
#include "Shader.h"
#include <stdexcept>
#include <utility>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gr
{

  GraphicsRenderer::GraphicsRenderer(const int width, const int height, std::string title)
  {
    m_window = std::make_unique<Window>(width, height, std::move(title));

    initOpenGL();

    m_nowTransform = glm::mat4(1.0f);
    m_currentFill = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
  }

  GraphicsRenderer::~GraphicsRenderer()
  {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);

    glfwTerminate();
  }

  void GraphicsRenderer::initOpenGL()
  {
    m_shader = std::make_unique<Shader>("shaders/shape.vert", "shaders/shape.frag");
    m_ellipseShader = std::make_unique<Shader>("shaders/ellipse.vert", "shaders/ellipse.frag");

    m_projection = glm::ortho(0.0f, static_cast<float>(m_width), static_cast<float>(m_height), 0.0f, -1.0f, 1.0f);

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  bool GraphicsRenderer::isAlive() const
  {
    return m_window->isAlive();
  }

  void GraphicsRenderer::clear()
  {
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);
  }

  void GraphicsRenderer::present() const
  {
    m_window->swapBuffers();
    m_window->pollEvents();
  }

  void GraphicsRenderer::rectangle(float x, float y, float width, float height) const
  {
    const float vertices[] = {
      x, y,
      x + width, y,
      x, y + height,
      x + width, y + height
    };

    m_shader->use();

    m_shader->setUniform("color", m_currentFill.r, m_currentFill.g, m_currentFill.b);
    m_shader->setUniform("projection", m_projection);
    m_shader->setUniform("transform", m_nowTransform);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0);
  }

  void GraphicsRenderer::triangle(float x1, float y1, float x2, float y2, float x3, float y3) const
  {
    const float vertices[] = {
      x1, y1,
      x2, y2,
      x3, y3
    };

    m_shader->use();
    m_shader->setUniform("color", m_currentFill.r, m_currentFill.g, m_currentFill.b);
    m_shader->setUniform("projection", m_projection);
    m_shader->setUniform("transform", m_nowTransform);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
  }

  void GraphicsRenderer::ellipse(float cx, float cy, float width, float height) const
  {
    const float x = cx - width / 2.0f;
    const float y = cy - height / 2.0f;

    const float vertices[] = {
      x, y,
      x + width, y,
      x, y + height,
      x + width, y + height
    };

    m_ellipseShader->use();

    m_ellipseShader->setUniform("color", m_currentFill.r, m_currentFill.g, m_currentFill.b);
    m_ellipseShader->setUniform("projection", m_projection);
    m_ellipseShader->setUniform("center", cx, cy);
    m_ellipseShader->setUniform("rad", width / 2.0f, height / 2.0f);
    m_ellipseShader->setUniform("transform", m_nowTransform);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0);
  }

  void GraphicsRenderer::translate(float x, float y)
  {
    m_nowTransform = glm::translate(m_nowTransform, glm::vec3(x, y, 0.0f));
  }

  void GraphicsRenderer::rotate(float angle)
  {
    m_nowTransform = glm::rotate(m_nowTransform, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
  }

  void GraphicsRenderer::scale(float x, float y)
  {
    m_nowTransform = glm::scale(m_nowTransform, glm::vec3(x, y, 1.0f));
  }

  void GraphicsRenderer::pushMatrix()
  {
    m_transformStack.push_back(m_nowTransform);
  }

  void GraphicsRenderer::popMatrix()
  {
    if (m_transformStack.empty())
    {
      return;
    }

    m_nowTransform = m_transformStack.back();
    m_transformStack.pop_back();
  }

  void GraphicsRenderer::fill(float r, float g, float b, float a)
  {
    m_currentFill = glm::vec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
  }

}
