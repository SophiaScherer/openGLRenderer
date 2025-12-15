#include <source/GraphicsRenderer.h>

int main()
{
  const auto renderer = gr::GraphicsRenderer(1000, 1000, "hello");

  while (renderer.isAlive())
  {
    renderer.clear();

    renderer.rectangle(-0.5f, -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f);
    renderer.rectangle(0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f);

    renderer.present();
  }

  return 0;
}