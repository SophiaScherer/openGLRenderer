#include <source/GraphicsRenderer.h>

int main()
{
  constexpr int width = 800;
  constexpr int height = 600;
  auto renderer = gr::GraphicsRenderer(width, height, "hello");

  while (renderer.isAlive())
  {
    gr::GraphicsRenderer::clear();

    renderer.pushTransformation();
      renderer.fill(1., 0.0, 0.5);
      renderer.rotate(45.);
      renderer.rectangle(0.0f, 0.0f, 150.0f, 150.0f);
    renderer.popTransformation();

    renderer.pushTransformation();
      renderer.translate(300.0f, 200.0f);
      renderer.triangle(0., 0., 100., 0., 50., 50.);
      //renderer.rectangle(0.0f, 0.0f, 100.0f, 100.0f, 0.0f, 0.0f, 1.0f);
    renderer.popTransformation();

    renderer.rectangle(400.0f, 300.0f, 100.0f, 100.0f);

    renderer.pushTransformation();
    renderer.translate(2.0f, 3.0f);
    renderer.triangle(400., 400., 500., 400., 450., 500.);
    renderer.popTransformation();

    renderer.ellipse(350., 350., 50., 50.);

    renderer.present();
  }

  return 0;
}