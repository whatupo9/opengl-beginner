#include <opengl-module/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Callbacks forward declarations
void framebufferSizeCallback(const GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

GL::~GL()
{
  destroyWindow();
}

void GL::destroyWindow()
{
  if (_window)
    glfwDestroyWindow(_window);

  glfwTerminate();
}

int GL::run(Callback updateCallback, Callback renderCallback, Callback initCallback, std::string windowName, int windowWidth, int windowHeight)
{
  _init = init(windowName, windowWidth, windowHeight);

  if (!_init)
    return -1;

  if (initCallback)
    initCallback();

  while (!glfwWindowShouldClose(_window))
  {
    processInput(_window);
    // Check for any events like key press or mouse clicks
    // Invokes appropriate callbacks
    glfwPollEvents();

    if (updateCallback)
      updateCallback();

    if (renderCallback)
      renderCallback();

    glfwSwapBuffers(_window);
  }

  destroyWindow();

  return 0;
}

bool GL::init(std::string windowName, int windowWidth, int windowHeight)
{
  if (!glfwInit())
  {
    std::cerr << "Could not init glfw\n";
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  _window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), NULL, NULL);
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
