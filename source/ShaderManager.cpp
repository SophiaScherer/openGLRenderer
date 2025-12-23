#include "ShaderManager.h"

namespace gr
{

  ShaderManager::ShaderManager()
  {
    loadShaders("polygon", "shaders/shape.vert", "shaders/shape.frag");
    loadShaders("ellipse", "shaders/ellipse.vert", "shaders/ellipse.frag");
  }

  void ShaderManager::loadShaders(const std::string& name, const char* vertexPath, const char* fragmentPath)
  {
    m_shaders[name] = std::make_unique<Shader>(vertexPath, fragmentPath);
  }

  Shader* ShaderManager::getShader(const std::string& name) const
  {
    return m_shaders.at(name).get();
  }

}
