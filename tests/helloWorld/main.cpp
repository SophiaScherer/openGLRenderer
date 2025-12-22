#include <source/GraphicsRenderer.h>
#include <cmath>

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

  renderer.fill(255, 0, 255);
  renderer.pushMatrix();
  renderer.translate(WIDTH / 2.0f, HEIGHT / 2.0f);
  renderer.rotate(45.0f * elapsedTime);
  renderer.translate(-25, -25);
  renderer.rectangle(0, 0, 50, 50);
  renderer.popMatrix();

  renderer.fill(255, 255, 0);
  renderer.pushMatrix();
  renderer.translate(WIDTH / 3.0f, HEIGHT * std::sin(0.1f * elapsedTime) / 3.0f);
  renderer.triangle(0, 0, 50, 0, 50, 50);
  renderer.popMatrix();

  renderer.fill(0, 255, 255);
  renderer.pushMatrix();
  renderer.translate(WIDTH / 4.0f, HEIGHT / 4.0f);
  renderer.scale(5.0f * std::cos(0.5f * elapsedTime) + 10.0f, 10);
  renderer.ellipse(0, 0, 10, 10);
  renderer.popMatrix();

  renderer.present();
}