#ifndef GRAPHICSRENDERER_H
#define GRAPHICSRENDERER_H

#include <GLFW/glfw3.h>

namespace gr
{

  class GraphicsRenderer
  {
  public:
    GraphicsRenderer();

  private:
    GLFWwindow* window;
  };

}

#endif //GRAPHICSRENDERER_H
