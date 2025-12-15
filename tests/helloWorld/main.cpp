#include <source/GraphicsRenderer.h>

int main()
{
  const auto renderer = gr::GraphicsRenderer(640, 480, "hello");

  while (renderer.isAlive())
  {
    renderer.clear();

    renderer.rectangle(100, 100, 200, 150, 1.0f, 0.0f, 0.0f);
    renderer.rectangle(300, 200, 100, 100, 0.0f, 0.0f, 1.0f);
    renderer.rectangle(-0.5f, -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f);

    renderer.present();
  }

  return 0;
}