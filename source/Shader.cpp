#include "Shader.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

namespace gr
{

  Shader::Shader (const char* vertexPath, const char* fragmentPath)
  {
    const auto vertexCode = readShaderFile(vertexPath);
    const auto fragmentCode = readShaderFile(fragmentPath);

    const auto vertex = loadVertexShader(vertexCode.c_str());
    const auto fragment = loadFragmentShader(fragmentCode.c_str());

    int success;

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertex);
    glAttachShader(m_ID, fragment);
    glLinkProgram(m_ID);

    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success)
    {
      char infoLog[512];
      glGetProgramInfoLog(m_ID, 512, nullptr, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
  }

  Shader::~Shader()
  {
    glDeleteProgram(m_ID);
  }

  void Shader::use() const
  {
    glUseProgram(m_ID);
  }

  void Shader::setUniform(const std::string& name, float r, float g, float b) const
  {
    glUniform3f(glGetUniformLocation(m_ID, name.c_str()), r, g, b);
  }

  void Shader::setUniform(const std::string& name, const glm::mat4& matrix) const
  {
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
  }

  void Shader::setUniform(const std::string& name, float x, float y) const
  {
    glUniform2f(glGetUniformLocation(m_ID, name.c_str()), x, y);
  }

  std::string Shader::readShaderFile(const std::string& filePath)
  {
    std::string shaderCode;
    std::ifstream vShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
      vShaderFile.open(filePath);
      std::stringstream vShaderStream;

      vShaderStream << vShaderFile.rdbuf();

      vShaderFile.close();

      shaderCode = vShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
      std::cout << "ERROR::SHADER::FILE_NOT_SUCCESS" << std::endl;
    }

    return shaderCode;
  }

  GLuint Shader::loadVertexShader(const char* shaderCode)
  {
    int success;

    const auto vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &shaderCode, nullptr);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      char infoLog[512];
      glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return vertex;
  }

  GLuint Shader::loadFragmentShader(const char* shaderCode)
  {
    int success;

    const auto fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &shaderCode, nullptr);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      char infoLog[512];
      glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
      std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << std::endl;
    }

    return fragment;
  }

}
