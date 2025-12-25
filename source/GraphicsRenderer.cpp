#include <glad/glad.h>
#include "GraphicsRenderer.h"
#include "Shader.h"
#include <utility>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace gr
{

  GraphicsRenderer::GraphicsRenderer(const int width, const int height, std::string title)
  {
    m_window = std::make_unique<Window>(width, height, std::move(title));

    m_shaderManager = std::make_unique<ShaderManager>();

    initOpenGL();

    m_shapeDrawer = std::make_unique<ShapeDrawer>(this);

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
    m_projection = glm::ortho(0.0f, static_cast<float>(m_window->getWidth()), static_cast<float>(m_window->getHeight()), 0.0f, -1.0f, 1.0f);

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

  // void GraphicsRenderer::setShadersForRendering(Shader* shader) const
  // {
  //   shader->use();
  //   shader->setUniform("color", m_currentFill.r, m_currentFill.g, m_currentFill.b);
  //   shader->setUniform("projection", m_projection);
  //   shader->setUniform("transform", m_nowTransform);
  // }

  void GraphicsRenderer::rectangle(float x, float y, float width, float height) const
  {
    m_shapeDrawer->rectangle(x, y, width, height);
  }

  void GraphicsRenderer::triangle(float x1, float y1, float x2, float y2, float x3, float y3) const
  {
    m_shapeDrawer->triangle(x1, y1, x2, y2, x3, y3);
  }

  void GraphicsRenderer::ellipse(float cx, float cy, float width, float height) const
  {
    m_shapeDrawer->ellipse(cx, cy, width, height);
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

  ShaderManager* GraphicsRenderer::getShaderManager()
  {
    return m_shaderManager.get();
  }

  glm::mat4 GraphicsRenderer::getProjection() const
  {
    return m_projection;
  }

  glm::mat4 GraphicsRenderer::getTransform() const
  {
    return m_nowTransform;
  }

  glm::vec4 GraphicsRenderer::getCurrentFill() const
  {
    return m_currentFill;
  }

  unsigned int GraphicsRenderer::getVAO() const
  {
    return m_VAO;
  }

  unsigned int GraphicsRenderer::getVBO() const
  {
    return m_VBO;
  }
}
