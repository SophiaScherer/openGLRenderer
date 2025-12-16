#include <source/GraphicsRenderer.h>

int main()
{
  const int width = 800;
  const int height = 600;
  const auto renderer = gr::GraphicsRenderer(width, height, "hello");

  while (renderer.isAlive())
  {
    renderer.clear();

    renderer.rectangle(300.0f, 200.0f, 100.0f, 100.0f, 0.0f, 0.0f, 1.0f);
    renderer.rectangle(400.0f, 300.0f, 100.0f, 100.0f, 1.0f, 0.0f, 0.0f);

    renderer.triangle(300., 200., 400., 200., 350., 100., 0.0, 1.0, 0.0);
    renderer.triangle(400., 400., 500., 400., 450., 500., 1.0, 0.0, 1.0);

    renderer.present();
  }

  return 0;
}