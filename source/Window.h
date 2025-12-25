#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GLFW/glfw3.h>

namespace gr {

  class Window {
  public:
    explicit Window(int width = 640, int height = 480, std::string  title = "Window!");
    ~Window();

    [[nodiscard]] bool isAlive() const;
    static void pollEvents() ;
    void swapBuffers() const;

    [[nodiscard]] int getWidth() const;
    [[nodiscard]] int getHeight() const;

  private:
    GLFWwindow* m_window = nullptr;
    int m_width;
    int m_height;
    std::string m_title;

    static void initGLFW();
    void createWindow();
    void initGLAD() const;
  };

}


#endif //WINDOW_H
