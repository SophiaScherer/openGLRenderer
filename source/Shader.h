#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

namespace gr
{

  class Shader
  {
  public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void use() const;

    void setUniform(const std::string& name, float r, float g, float b) const;
    void setUniform(const std::string& name, const glm::mat4& mat) const;
    void setUniform(const std::string& name, float x, float y) const;

  private:
    unsigned int ID;

    [[nodiscard]] static std::string readShaderFile(const std::string& filePath) ;

    static GLuint loadVertexShader(const char* shaderCode) ;
    static GLuint loadFragmentShader(const char* shaderCode) ;
  };
}

#endif //SHADER_H