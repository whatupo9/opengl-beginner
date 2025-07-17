#ifndef GL_H
#define GL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef void (*Callback)();

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

class GL
{
  GLFWwindow* _window = nullptr;

  GL() = default;

public:
  GL(const GL&) = delete;
  GL& operator=(const GL&) = delete;

  ~GL();

  static GL& getInstance();

  GLFWwindow* getWindow() const
  {
    return _window;
  }

  int run(Callback update, Callback render, Callback initCallback);

private:
  bool init();
};

#endif // !GL_H
