#pragma once

#include "VertexBuffer.hpp"

#include "glad/glad.h"

#include <cassert>
#include <iostream>

class VertexArray final
{
public:
  VertexArray() : M_array{0U}
  {
    std::cerr << "Default constructing vertex array\n";
  }

  VertexArray(const GLuint array) : M_array{array}
  {
    std::cerr << "Constructing vertex array\n";

    if (array != 0U)
      return;
    
    glGenVertexArrays(1, &M_array);
    this->Bind();
  }

  VertexArray(VertexArray &&other) noexcept : M_array{other.M_array}
  {
    std::cerr << "Move constructing vertex array\n";
    other.M_array = 0U;
  }

  VertexArray &operator=(VertexArray &&other)
  {
    std::cerr << "Move assigning vertex array\n";

    if (this != &other)
    {
      glDeleteVertexArrays(1, &M_array);
      this->M_array = other.M_array;
      other.M_array = 0U;
    }
    return *this;
  }

  VertexArray(const VertexArray &) = delete;
  VertexArray &operator=(const VertexArray &) = delete;

  ~VertexArray()
  {
    std::cerr << "Destructing vertex array\n";
    glDeleteVertexArrays(1, &M_array);
  }

  template <typename T, std::size_t N>
  void Link(const VertexBuffer<T, N>& vertexBuffer, const GLuint layout) const
  {
    vertexBuffer.Bind();

    if (typeid(T) == typeid(GLfloat))
      glVertexAttribPointer(layout, N, GL_FLOAT, GL_FALSE, 0, nullptr);
    else
      throw std::invalid_argument("Unsupported vertex buffer type, expected GLfloat");

    glEnableVertexAttribArray(layout);

    vertexBuffer.Stop();
  }

  void Bind() const
  {
    assert(M_array != 0U);
    glBindVertexArray(M_array);
  }

  void Unbind() const
  {
    assert(M_array != 0U);
    glBindVertexArray(0U);
  }

private:
  GLuint M_array;
};
