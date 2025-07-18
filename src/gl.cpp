#include <opengl-module/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Callbacks forward declarations

/**
 * Callback for window resize
 *
 * @param window: A pointer to the glfw window
 * @param width:  The new width
 * @param height: The new height
 */
void framebufferSizeCallback(const GLFWwindow* window, int width, int height);

/**
 * Callback for checking input each frame
 *
 * @param window: A pointer to the glfw window
 */
void processInput(GLFWwindow* window);

// GL Destructor
GL::~GL()
{
  destroyWindow();
}

/**
 * Initializes class and runs the render loop
 *
 * @param updateCallback: A function called every frame for any updates required
 * @param renderCallback: A function called every frame to handle rendering
 *                        You must make all of the opengl calls yourself
 *                        This class just handles the window creation and the render loop
 *                        The rest is up to you
 * @param initCallback:   A function called once GL is initialized.
 *                        Can be used to setup any OpenGL objects before the render loop
 * @param windowName:     The name to give the window
 * @param windowWidth:    The width of the window, in pixels
 * @param windowHeight:   The height of the window, in pixels
 *
 * @returns 0 for ok, -1 for error
 */
int GL::run(Callback updateCallback, Callback renderCallback, Callback initCallback, std::string windowName, int windowWidth, int windowHeight)
{
  // Initialize glfw and glad
  _init = init(windowName, windowWidth, windowHeight);

  // Check if initialization failed
  if (!_init)
    return -1;

  // Call the init callback, if not nullptr
  if (initCallback)
    initCallback();

  // Loop until the window should close
  while (!glfwWindowShouldClose(_window))
  {
    // Check for input
    processInput(_window);

    // Check for any events like key press or mouse clicks
    // Invokes appropriate callbacks
    glfwPollEvents();

    // Call update callback if not nullptr
    if (updateCallback)
      updateCallback();

    // Call render callback if not nullptr
    if (renderCallback)
      renderCallback();

    glfwSwapBuffers(_window);
  }

  // Handle deallocation of resources after the window should close
  destroyWindow();

  // Return 0, function exited without error
  return 0;
}

/**
 * Handles the creation of the context and window
 * Loads gl with glad
 *
 * @param windowName:   The name of the window
 * @param windowWidth:  The width of the window, in pixels
 * @param windowHeight: The height of the window, in pixels
 *
 * @returns True if initialization succeeded
 */
bool GL::init(std::string windowName, int windowWidth, int windowHeight)
{
  // Initialize glfw, and return false if there was an error
  if (!glfwInit())
  {
    std::cerr << "Could not init glfw\n";
    return false;
  }

  // Set opengl version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create the window and the context
  _window = glfwCreateWindow(windowWidth, windowHeight, windowName.c_str(), NULL, NULL);
  glfwMakeContextCurrent(_window);

  // Check for errors during window creation
  if (!_window)
  {
    std::cerr << "Could not create window or context\n";
    return false;
  }

  // Load GL with glad, and check for errors
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    return false;
  }

  // Set the viewport and window resize callback
  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  glfwSetFramebufferSizeCallback(_window, (GLFWframebuffersizefun)framebufferSizeCallback);

  // No errors occured, so return true
  return true;
}

/**
 * Destroys the window and terminates OpenGL
 * Uninitializes glfw and glad
 */
void GL::destroyWindow()
{
  // If GL is not initialized, there is nothing to deallocate
  if (!_init)
    return;

  if (_window)
    glfwDestroyWindow(_window);

  glfwTerminate();

  _init = false;
}

/**
 * Callback for window resize
 *
 * @param window: A pointer to the glfw window
 * @param width:  The new width
 * @param height: The new height
 */
void framebufferSizeCallback(const GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

/**
 * Callback for checking input each frame
 *
 * @param window: A pointer to the glfw window
 */
void processInput(GLFWwindow* window)
{
  // If the user presses escape, close the window
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
