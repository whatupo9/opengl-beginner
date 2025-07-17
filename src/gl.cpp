#include "gl.h"
#include <GLFW/glfw3.h>
#include <iostream>

// Callbacks forward declarations
void framebufferSizeCallback(const GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

GL::~GL()
{
  if (_window)
    glfwDestroyWindow(_window);

  glfwTerminate();
}

GL& GL::getInstance()
{
  static GL instance;
  return instance;
}

int GL::run(Callback update, Callback render, Callback initCallback)
{
  if (!init())
    return -1;

  if (initCallback)
    initCallback();

  while (!glfwWindowShouldClose(_window))
  {
    processInput(_window);
    // Check for any events like key press or mouse clicks
    // Invokes appropriate callbacks
    glfwPollEvents();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (update)
      update();

    if (render)
      render();

    glfwSwapBuffers(_window);
  }

  return 0;
}

bool GL::init()
{
  if (!glfwInit())
  {
    std::cerr << "Could not init glfw\n";
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  _window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Cube Simulator", NULL, NULL);
  glfwMakeContextCurrent(_window);

  if (!_window)
  {
    std::cerr << "Could not create window or context\n";
    return false;
  }

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    return false;
  }

  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glfwSetFramebufferSizeCallback(_window, (GLFWframebuffersizefun)framebufferSizeCallback);

  return true;
}

void framebufferSizeCallback(const GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
