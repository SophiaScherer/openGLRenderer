#ifndef GRAPHICSRENDERER_H
#define GRAPHICSRENDERER_H

#include <memory>
#include <GLFW/glfw3.h>
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
    void run() const;

  private:
    GLFWwindow* window;
    int width;
    int height;
    std::string title;
    std::unique_ptr<Shader> shader;

    void initWindow();
    static void cleanUp();
  };

}

#endif //GRAPHICSRENDERER_H
