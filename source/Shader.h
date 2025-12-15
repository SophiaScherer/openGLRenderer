#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>

namespace gr
{

  class Shader
  {
  public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void use() ;
    void setBool(const std::string& name, bool value) ;
    void setInt(const std::string& name, int value) ;
    void setFloat(const std::string& name, float value) ;
    unsigned int ID;

  private:
  };
}

#endif //SHADER_H