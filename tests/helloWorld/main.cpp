#include <source/GraphicsRenderer.h>

int main()
{
  constexpr float width = 800;
  constexpr float height = 600;
  auto renderer = gr::GraphicsRenderer(width, height, "hello");

  while (renderer.isAlive())
  {
    gr::GraphicsRenderer::clear();

    renderer.fill(255, 0, 255);
    renderer.pushMatrix();
      renderer.translate(width / 2.0f, height / 2.0f);
      renderer.rotate(45);
      renderer.rectangle(0, 0, 50, 50);
    renderer.popMatrix();

    renderer.fill(255, 255, 0);
    renderer.pushMatrix();
      renderer.translate(width / 3.0f, height / 3.0f);
      renderer.triangle(0, 0, 50, 0, 50, 50);
    renderer.popMatrix();

    renderer.fill(0, 255, 255);
    renderer.pushMatrix();
      renderer.translate(width / 4.0f, height / 4.0f);
      renderer.scale(5, 5);
      renderer.ellipse(0, 0, 10, 10);
    renderer.popMatrix();


    renderer.present();
  }

  return 0;
}