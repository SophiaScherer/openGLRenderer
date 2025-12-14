#include <source/GraphicsRenderer.h>

int main()
{
  const auto renderer = gr::GraphicsRenderer(640, 480, "hello");
  renderer.run();

  
}