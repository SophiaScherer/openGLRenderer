#ifndef GRAPHICSRENDERER_H
#define GRAPHICSRENDERER_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <memory>
#include <string>

namespace gr
{
  class Shader;
  class GraphicsRenderer
  {
  public:
    explicit GraphicsRenderer(int width = 640, int height = 480, std::string  = "Window!");
    ~GraphicsRenderer();
    [[nodiscard]] bool isAlive() const;
    void clear() const;
    void present() const;
    void rectangle(float x,
                   float y,
                   float width,
                   float height,
                   float r,
                   float g,
                   float b) const;

    void triangle(float x1,
                  float y1,
                  float x2,
                  float y2,
                  float x3,
                  float y3,
                  float r,
                  float g,
                  float b) const;

    // void ellipseOld(float cx,
    //              float cy,
    //              float xRad,
    //              float yRad,
    //              int segments,
    //              float r,
    //              float g,
    //              float b) const;

    void ellipse(float cx,
                  float cy,
                  float xRad,
                  float yRad,
                  float r,
                  float g,
                  float b) const;

  private:
    GLFWwindow* window;
    int width;
    int height;
    std::string title;

    std::unique_ptr<Shader> shader;
    std::unique_ptr<Shader> ellipseShader;
    unsigned int VAO;
    unsigned int VBO;
    glm::mat4 projection;

    void initWindow();
    void initOpenGL();
    void cleanUp();
  };

}

#endif //GRAPHICSRENDERER_H
