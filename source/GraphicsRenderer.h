#ifndef GRAPHICSRENDERER_H
#define GRAPHICSRENDERER_H

#include <GLFW/glfw3.h>
#include <string>

namespace gr
{

  class GraphicsRenderer
  {
  public:
    GraphicsRenderer(int width = 640, int height = 480, const std::string& = "Window!");
    ~GraphicsRenderer();

    void run() const;

  private:
    GLFWwindow* window;
    int width;
    int height;
    std::string title;

    void initWindow();
    static void cleanUp();
  };

}

#endif //GRAPHICSRENDERER_H
