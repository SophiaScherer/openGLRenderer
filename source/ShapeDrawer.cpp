#include "ShapeDrawer.h"
#include "GraphicsRenderer.h"

namespace gr {

  ShapeDrawer::ShapeDrawer(GraphicsRenderer* renderer)
  : m_renderer(renderer), m_shaderManager(renderer->getShaderManager()) {}

  void ShapeDrawer::rectangle(float x, float y, float width, float height) const
  {
    const float vertices[] = {
      x, y,
      x + width, y,
      x, y + height,
      x + width, y + height
    };

    setShadersForRendering("polygon");

    glBindVertexArray(m_renderer->getVAO());
    glBindBuffer(GL_ARRAY_BUFFER, m_renderer->getVBO());
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(0);
  }

  void ShapeDrawer::triangle(float x1, float y1, float x2, float y2, float x3, float y3) const
  {
    const float vertices[] = {
      x1, y1,
      x2, y2,
      x3, y3
    };

    setShadersForRendering("polygon");

    glBindVertexArray(m_renderer->getVAO());
    glBindBuffer(GL_ARRAY_BUFFER, m_renderer->getVBO());
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
  }

  void ShapeDrawer::ellipse(float cx, float cy, float width, float height) const
  {
  }

  void ShapeDrawer::setShadersForRendering(const std::string& shaderName) const
  {
    Shader* shader = m_shaderManager->getShader(shaderName);
    shader->use();

    shader->setUniform("color", m_renderer->getCurrentFill().r,
                                        m_renderer->getCurrentFill().g,
                                        m_renderer->getCurrentFill().b);
    shader->setUniform("projection", m_renderer->getProjection());
    shader->setUniform("transformation", m_renderer->getTransform());
  }
}
