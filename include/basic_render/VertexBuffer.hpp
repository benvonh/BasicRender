#pragma once

#include "glad/glad.h"

#include <array>
#include <cassert>
#include <iostream>

template <typename T, std::size_t N>
class VertexBuffer final
{
public:
  VertexBuffer() : M_buffer{0U}, M_vertices{}
  {
    std::cerr << "Default constructing vertex buffer\n";
  }

  VertexBuffer(const GLuint buffer) : M_buffer{buffer}, M_vertices{}
  {
    std::cerr << "Constructing vertex buffer\n";
    
    if (buffer != 0U)
      return;

    glGenBuffers(1, &M_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, M_buffer);
    glBufferData(GL_ARRAY_BUFFER, M_vertices.size(), M_vertices.data(), GL_STATIC_DRAW);
  }

  VertexBuffer(VertexBuffer &&other) noexcept : M_buffer{other.M_buffer}, M_vertices{other.M_vertices}
  {
    std::cerr << "Move constructing vertex buffer\n";
    other.M_buffer = 0U;
  }

  VertexBuffer &operator=(VertexBuffer &&other) noexcept
  {
    std::cerr << "Move assigning vertex buffer\n";

    if (this != &other)
    {
      glDeleteBuffers(1, &M_buffer);
      this->M_vertices = other.M_vertices;
      this->M_buffer = other.M_buffer;
      other.M_buffer = 0U;
    }
    return *this;
  }

  VertexBuffer(const VertexBuffer &) = delete;
  VertexBuffer &operator=(const VertexBuffer &) = delete;

  ~VertexBuffer()
  {
    std::cerr << "Destructing vertex buffer\n";
    glDeleteBuffers(1, &M_buffer);
  }

  void Bind() const
  {
    assert(M_buffer != 0U);
    glBindBuffer(GL_ARRAY_BUFFER, M_buffer);
  }

  void Unbind() const
  {
    assert(M_buffer != 0U);
    glBindBuffer(GL_ARRAY_BUFFER, 0U);
  }

  void Copy(const std::array<T, N>& vertices)
  {
    M_vertices = vertices;
  }

private:
  GLuint M_buffer;
  std::array<T, N> M_vertices;
};
