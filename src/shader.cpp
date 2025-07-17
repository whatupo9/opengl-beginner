#include <string.h>
#include <shader.h>
#include <fstream>
#include <iostream>
#include <sstream>

/**
 * Shader Constructor
 *
 * @param vertexPath: The relative file path to the vertex shader
 * @param fragmentPath: The relative file path to the fragment shader
 */
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
  // retrieve the vertex/fragment source code from filePath
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  // ensure ifstream objects can throw exceptions:
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try
  {
    std::string longVertexPath = std::string(SHADERS_DIR) + vertexPath;
    std::string longFragmentPath = std::string(SHADERS_DIR) + fragmentPath;

    // open files
    vShaderFile.open(longVertexPath);
    fShaderFile.open(longFragmentPath);

    if (!vShaderFile.is_open() || !fShaderFile.is_open())
      throw std::ifstream::failure("Failed to open shader files");

    std::stringstream vShaderStream;
    std::stringstream fShaderStream;

    // read file's buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    // close file handlers
    vShaderFile.close();
    fShaderFile.close();

    // convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  }
  catch (const std::ifstream::failure& e)
  {
    std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << "\n";
    std::cerr << "Attempted to read: " << vertexPath << " and " << fragmentPath << "\n";

    // Check which file(s) failed to open
    if (!vShaderFile.is_open())
      std::cerr << "Failed to open vertex shader: " << vertexPath << "\n";
    if (!fShaderFile.is_open())
      std::cerr << "Failed to open fragment shader: " << fragmentPath << "\n";
  }

  const char* vShaderCode = vertexCode.c_str();
  const char* fShaderCode = fragmentCode.c_str();

  // Store error info
  int success;
  char infoLog[512];

  // Create the vertex shader
  GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vShader, 1, &vShaderCode, nullptr);
  glCompileShader(vShader);

  // Check for vertex shader compile errors
  glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vShader, 512, nullptr, infoLog);
    std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << "\n";
  }

  // Create the fragment shader
  GLuint fShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(fShader, 1, &fShaderCode, nullptr);
  glCompileShader(fShader);

  // Check for fragment shader compile errors
  glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fShader, 512, nullptr, infoLog);
    std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << "\n";
  }

  // Create the shader program
  _id = glCreateProgram();
  glAttachShader(_id, vShader);
  glAttachShader(_id, fShader);
  glLinkProgram(_id);

  glGetProgramiv(_id, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(_id, 512, NULL, infoLog);
    std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << "\n";
  }

  // Delete the shaders after the program has been linked
  glDeleteShader(vShader);
  glDeleteShader(fShader);
}

/**
 * Instructs OpenGL to use this shader for rendering
 */
void Shader::use()
{
  glUseProgram(_id);
}

/**
 * Sets a bool uniform in the shader
 *
 * @param name: The name of the uniform to be set
 * @param value: The value to assign
 */
void Shader::setBool(const std::string& name, bool value) const
{
  glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value);
}

/**
 * Sets an int uniform in the shader
 *
 * @param name: The name of the uniform to be set
 * @param value: The value to assign
 */
void Shader::setInt(const std::string& name, int value) const
{
  glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
}

/**
 * Sets a float uniform in the shader
 *
 * @param name: The name of the uniform to be set
 * @param value: The value to assign
 */
void Shader::setFloat(const std::string& name, float value) const
{
  glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
}
