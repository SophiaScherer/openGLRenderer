#ifndef GRAPHICSRENDERER_H
#define GRAPHICSRENDERER_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <memory>
#include <string>

namespace gr
{
  class Shader;
  class GraphicsRenderer
  {
  public:
    explicit GraphicsRenderer(int width = 640, int height = 480, std::string  = "Window!");
    ~GraphicsRenderer();
    [[nodiscard]] bool isAlive() const;
    static void clear() ;
    void present() const;
    void rectangle(float x,
                   float y,
                   float width,
                   float height) const;

    void triangle(float x1,
                  float y1,
                  float x2,
                  float y2,
                  float x3,
                  float y3) const;

    void ellipse(float cx,
                  float cy,
                  float xRad,
                  float yRad) const;

    void translate(float x, float y);
    void rotate(float angle);
    void scale(float x, float y);
    void pushTransformation();
    void popTransformation();
    void fill(float r,
              float g,
              float b,
              float a = 255.0f);

  private:
    GLFWwindow* window;

    int width;
    int height;
    std::string title;

    std::unique_ptr<Shader> shader;
    std::unique_ptr<Shader> ellipseShader;
    unsigned int VAO{};
    unsigned int VBO{};

    glm::mat4 projection{};
    glm::mat4 nowTransform{};
    std::vector<glm::mat4> transformStack{};
    glm::vec4 currentFill = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    void initWindow();
    void initOpenGL();
    void cleanUp() const;
  };

}

#endif //GRAPHICSRENDERER_H
