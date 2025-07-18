#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <string>

// Wrapper for a shader program in OpenGL
class Shader
{
  GLuint _id; // the program ID

  bool _init = false;             // Track if the shader has been initialized
  bool _initErrorPrinted = false; // Track if an error message about the init status has been printed

public:
  /**
   * Shader Default Constructor
   * DOES NOT INITIALIZE
   * This constructor is only to allow global instances
   * After constructing a Shader, you must call Shader::init()
   */
  Shader() = default;

  /**
   * Shader Constructor
   *
   * @param vertexPath: The relative file path to the vertex shader
   * @param fragmentPath: The relative file path to the fragment shader
   */
  Shader(const char* vertexPath, const char* fragmentPath);

  /**
   * Initializes the shader
   * Compile the vertex and fragment shaders
   * Attaches them to a shader program and links it
   *
   * @param vertexPath: The relative file path to the vertex shader
   * @param fragmentPath: The relative file path to the fragment shader
   */
  void init(const char* vertexPath, const char* fragmentPath);

  /**
   * Instructs OpenGL to use this shader for rendering
   */
  void use();

  /**
   * Gets the id of the shader program
   *
   * @returns: The id of the shader program
   */
  GLuint getID() const
  {
    return _id;
  }

  /**
   * Sets a bool uniform in the shader
   *
   * @param name: The name of the uniform to be set
   * @param value: The value to assign
   */
  void setBool(const std::string& name, bool value) const;

  /**
   * Sets an int uniform in the shader
   *
   * @param name: The name of the uniform to be set
   * @param value: The value to assign
   */
  void setInt(const std::string& name, int value) const;

  /**
   * Sets a float uniform in the shader
   *
   * @param name: The name of the uniform to be set
   * @param value: The value to assign
   */
  void setFloat(const std::string& name, float value) const;
};

#endif
