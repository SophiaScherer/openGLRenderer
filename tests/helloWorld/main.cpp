#include <source/GraphicsRenderer.h>
#include <iostream>

constexpr float WIDTH = 800;
constexpr float HEIGHT = 600;

void doRendering(gr::GraphicsRenderer& renderer);

int main()
{
  auto renderer = gr::GraphicsRenderer(WIDTH, HEIGHT, "Window!!");

  while (renderer.isAlive())
  {
    doRendering(renderer);
  }
}

void doRendering(gr::GraphicsRenderer& renderer)
{
  gr::GraphicsRenderer::clear();

  static float elapsedTime = 0.0f;

  float dt = renderer.getDeltaTime();
  elapsedTime += dt * 10.0f;

  std::cout << "elapsedTime: " << elapsedTime << std::endl;

  renderer.fill(255, 0, 255);
  renderer.pushMatrix();
  renderer.translate(WIDTH / 2.0f, HEIGHT / 2.0f);
  renderer.rotate(45.0 * elapsedTime);
  renderer.rectangle(0, 0, 50, 50);
  renderer.popMatrix();

  renderer.fill(255, 255, 0);
  renderer.pushMatrix();
  renderer.translate(WIDTH / 3.0f, HEIGHT / 3.0f);
  renderer.triangle(0, 0, 50, 0, 50, 50);
  renderer.popMatrix();

  renderer.fill(0, 255, 255);
  renderer.pushMatrix();
  renderer.translate(WIDTH / 4.0f, HEIGHT / 4.0f);
  renderer.scale(10, 10);
  renderer.ellipse(0, 0, 10, 10);
  renderer.popMatrix();

  renderer.present();
}