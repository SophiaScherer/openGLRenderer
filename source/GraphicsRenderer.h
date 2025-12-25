#ifndef GRAPHICSRENDERER_H
#define GRAPHICSRENDERER_H

#include "ShaderManager.h"
#include "Window.h"
#include <glm/glm.hpp>
#include <memory>
#include <string>

namespace gr
{

  class Shader;

  class GraphicsRenderer
  {
  public:
    explicit GraphicsRenderer(int width = 640, int height = 480, std::string = "Window!");

    ~GraphicsRenderer();

    [[nodiscard]] bool isAlive() const;

    static void clear();

    void present() const;

    void rectangle(float x,
                   float y,
                   float width,
                   float height) const;

    void triangle(float x1,
                  float y1,
                  float x2,
                  float y2,
                  float x3,
                  float y3) const;

    void ellipse(float cx,
                  float cy,
                  float width,
                  float height) const;

    void translate(float x, float y);
    void rotate(float angle);
    void scale(float x, float y);
    void pushMatrix();
    void popMatrix();

    void fill(float r,
              float g,
              float b,
              float a = 255.0f);

    ShaderManager* getShaderManager();
    [[nodiscard]] glm::mat4 getProjection() const;
    [[nodiscard]] glm::mat4 getTransform() const;
    [[nodiscard]] glm::vec4 getCurrentFill() const;
    [[nodiscard]] unsigned int getVAO() const;
    [[nodiscard]] unsigned int getVBO() const;

  private:
    // Window
    std::unique_ptr<Window> m_window;

    // shaders
    std::unique_ptr<ShaderManager> m_shaderManager;

    // vertex objects
    unsigned int m_VAO{};
    unsigned int m_VBO{};

    // world coordinate projection
    glm::mat4 m_projection{};

    // shape drawing config
    glm::mat4 m_nowTransform{};
    std::vector<glm::mat4> m_transformStack{};
    glm::vec4 m_currentFill = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    void initOpenGL();

    void setShadersForRendering(Shader* shader) const;
  };

}

#endif //GRAPHICSRENDERER_H
