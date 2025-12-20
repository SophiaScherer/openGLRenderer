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
      renderer.fill(1.0, 0.0, 1.0);
      renderer.translate(width/2., height/2.);
      renderer.rectangle(0.0, 0.0, 50.0, 50.0);
    renderer.popTransformation();

    renderer.pushTransformation();
      renderer.translate(width/3., height/3.);
      renderer.triangle(0.0, 0.0, 50.0, 0.0, 50.0, 50.0);
    renderer.popTransformation();

    renderer.pushTransformation();
      renderer.translate(width/4., height/4.);
      renderer.scale(5., 5.);
      renderer.ellipse(0.0, 0.0, 10., 10.);
    renderer.popTransformation();


    renderer.present();
  }

  return 0;
}