#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <string>
#include <unordered_map>
#include <memory>

#include "Shader.h"

namespace gr
{

  class ShaderManager {
  public:
    ShaderManager();
    ~ShaderManager() = default;

    void loadShaders(const std::string& name, const char* vertexPath, const char* fragmentPath);
    Shader* getShader(const std::string& name) const;

  private:
    std::unordered_map<std::string, std::unique_ptr<Shader>> m_shaders;
  };

}

#endif //SHADERMANAGER_H
