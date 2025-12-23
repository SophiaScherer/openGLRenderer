#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GLFW/glfw3.h>

namespace gr {

  class Window {
  public:
    explicit Window(int width = 640, int height = 480, std::string title = "Window!");
    ~Window();

    bool isAlive() const;
    void pollEvents() const;
    void swapBuffers() const;

  private:
    GLFWwindow* m_window = nullptr;
    int m_width;
    int m_height;
    std::string m_title;

    void initGLFW();
    void createWindow();
    void initGLAD();
  };

}


#endif //WINDOW_H
