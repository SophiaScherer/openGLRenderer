#include "ShaderManager.h"

namespace gr
{

  ShaderManager::ShaderManager()
  {
    loadShaders("polygonShader", "shaders/polygon.vert", "shaders/polygon.frag");
    loadShaders("ellipseShader", "shaders/ellipse.vert", "shaders/ellipse.frag");
  }

  void ShaderManager::loadShaders(const std::string& name, const char* vertexPath, const char* fragmentPath)
  {
    m_shaders[name] = std::make_unique<Shader>(vertexPath, fragmentPath);
  }
}
