#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <string>

class Shader
{
  // the program ID
  GLuint _id;

public:
  /**
   * Shader Constructor
   *
   * @param vertexPath: The relative file path to the vertex shader
   * @param fragmentPath: The relative file path to the fragment shader
   */
  Shader(const char* vertexPath, const char* fragmentPath);

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
