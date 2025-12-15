#ifndef GRAPHICSRENDERER_H
#define GRAPHICSRENDERER_H

#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include "glm/vec3.hpp"

namespace gr
{
  class Shader;
  class GraphicsRenderer
  {
  public:
    explicit GraphicsRenderer(int width = 640, int height = 480, std::string  = "Window!");
    ~GraphicsRenderer();
    [[nodiscard]] bool isAlive() const;
    //void run() const;
    void clear() const;
    void present() const;
    void rectangle(float x, float y,
                   float width, float height,
                   float r, float g, float b) const;

  private:
    GLFWwindow* window;
    int width;
    int height;
    std::string title;

    std::unique_ptr<Shader> shader;
    unsigned int VAO;
    unsigned int VBO;

    void initWindow();
    void initOpenGL();
    void cleanUp();
  };

}

#endif //GRAPHICSRENDERER_H
