#ifndef GL_H
#define GL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

// Define a function pointer for event callback
typedef void (*Callback)();

// Constants for window size

const int WINDOW_WIDTH = 800;  // Default window width, in pixels
const int WINDOW_HEIGHT = 600; // Default window height, in pixels

// Handles window creation and render loop for OpenGL
// Uses a singleton to possibility of multiple windows
class GL
{
  GLFWwindow* _window = nullptr; // Stores a pointer to the window
  bool _init = false;            // Tracks if glfw and glad have been initialized

  // Default Constructor
  // Private for singleton
  GL() = default;

public:
  // Delete copy ctor and assignment operator to prevent copying of singleton
  GL(const GL&) = delete;
  GL& operator=(const GL&) = delete;

  // GL Destructor
  ~GL();

  /**
   * Returns a reference to a static instance of this class
   *
   * This class uses a singleton, so any non-static methods
   * must be invoked through this reference
   */
  static GL& getInstance()
  {
    static GL instance;
    return instance;
  }

  // Checks if the window is initialized
  bool isInitialized()
  {
    return _init;
  }

  // Gets the window pointer
  GLFWwindow* getWindow() const
  {
    return _window;
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
  int run(Callback updateCallback, Callback renderCallback, Callback initCallback, std::string windowName, int windowWidth = WINDOW_WIDTH, int windowHeight = WINDOW_HEIGHT);

private:
  /**
   * Handles the creation of the context and window
   * Loads gl with glad
   *
   * @param windowName:   The name of the window
   * @param windowWidth:  The width of the window, in pixels
   * @param windowHeight:  The height of the window, in pixels
   *
   * @returns True if initialization succeeded
   */
  bool init(std::string windowName, int windowWidth, int windowHeight);

  /**
   * Destroys the window and terminates OpenGL
   * Uninitializes glfw and glad
   */
  void destroyWindow();
};

#endif // !GL_H
