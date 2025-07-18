#ifndef GL_H
#define GL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

typedef void (*Callback)();

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

class GL
{
  GLFWwindow* _window = nullptr; // Stores a pointer to the window
  bool _init = false;            // Tracks if glfw and glad have been initialized

  GL() = default;

public:
  GL(const GL&) = delete;
  GL& operator=(const GL&) = delete;

  ~GL();

  void destroyWindow();

  static GL& getInstance()
  {
    static GL instance;
    return instance;
  }

  bool isInitialized()
  {
    return _init;
  }

  GLFWwindow* getWindow() const
  {
    return _window;
  }

  int run(Callback updateCallback, Callback renderCallback, Callback initCallback, std::string windowName, int windowWidth = WINDOW_WIDTH, int windowHeight = WINDOW_HEIGHT);

private:
  bool init(std::string windowName, int windowWidth, int windowHeight);
};

#endif // !GL_H
