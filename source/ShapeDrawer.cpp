#include "ShapeDrawer.h"
#include "GraphicsRenderer.h"

namespace gr {

  ShapeDrawer::ShapeDrawer(GraphicsRenderer* renderer)
  : m_renderer(renderer), m_shaderManager(renderer->getShaderManager()) {}

  void ShapeDrawer::rectangle(float x, float y, float width, float height) const
  {
  }

  void ShapeDrawer::triangle(float x1, float y1, float x2, float y2, float x3, float y3) const
  {
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
