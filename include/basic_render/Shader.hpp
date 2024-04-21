#pragma once

#include "glad/glad.h"

#include <string>
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>

class Shader final
{
public:
  Shader() : M_program{0U}
  {
    std::cerr << "Default constructing shader\n";
  }

  Shader(const std::filesystem::path &vertexPath, const std::filesystem::path &fragmentPath)
      : M_program{glCreateProgram()}
  {
    std::cerr << "Constructing shader\n";

    const auto create_shader = [](const std::filesystem::path &path, const GLenum type) -> GLuint
    {
      const std::ifstream file(path);
      std::stringstream stream;

      if (!file)
        throw std::runtime_error("Failed to open file: " + path.string());

      stream << file.rdbuf();

      const std::string buffer = stream.str();
      const char* source = buffer.c_str();

      const GLuint shader = glCreateShader(type);

      glShaderSource(shader, 1, &source, nullptr);
      glCompileShader(shader);

      GLint ok = 0;
      glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);

      if (!ok)
      {
        GLchar log[1024] = "No message";
        glGetShaderInfoLog(shader, 1024, nullptr, log);
        std::cerr << "[Shader] " << log << std::endl;
        throw std::runtime_error("Failed to compile shader!");
      }

      return shader;
    };

    const GLuint vertex = create_shader(vertexPath, GL_VERTEX_SHADER);
    const GLuint fragment = create_shader(fragmentPath, GL_FRAGMENT_SHADER);

    glAttachShader(M_program, vertex);
    glAttachShader(M_program, fragment);
    glLinkProgram(M_program);

    GLint ok = 0;
    glGetProgramiv(M_program, GL_LINK_STATUS, &ok);

    if (!ok)
    {
      GLchar log[1024] = "No message";
      glGetProgramInfoLog(M_program, 1024, nullptr, log);
      std::cerr << "[Shader] " << log << std::endl;
      throw std::runtime_error("Failed to link program!");
    }

    glDeleteShader(fragment);
    glDeleteShader(vertex);
  }

  Shader(Shader &&other) noexcept : M_program{other.M_program}
  {
    std::cerr << "Move constructing shader\n";
    other.M_program = 0U;
  }

  Shader &operator=(Shader &&other) noexcept
  {
    std::cerr << "Move assigning shader\n";

    if (this != &other)
    {
      glDeleteProgram(this->M_program);
      this->M_program = other.M_program;
      other.M_program = 0U;
    }
    return *this;
  }

  Shader(const Shader &) = delete;
  Shader &operator=(const Shader &) = delete;

  ~Shader()
  {
    std::cerr << "Destructing shader\n";
    glDeleteProgram(M_program);
  }

  void Use() const
  {
    assert(M_program != 0U);
    glUseProgram(M_program);
  }

private:
  GLuint M_program;
};
