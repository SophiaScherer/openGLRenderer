#ifndef SHADERS_H
#define SHADERS_H

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
    void setMat4(const std::string& name, const glm::mat4& matrix) const;

    unsigned int ID;

  private:
    static std::string readFile(const char* path);
    static void checkCompileErrors(unsigned int shader, const std::string& type);
  };
}

#endif //SHADERS_H