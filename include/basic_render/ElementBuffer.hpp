#pragma once

#include "glad/glad.h"

#include <array>
#include <cassert>
#include <iostream>

template <typename T, std::size_t N>
class ElementBuffer final
{
public:
  ElementBuffer() : M_buffer{0U}, M_elements{}
  {
    std::cerr << "Default constructing element buffer\n";
  }

  ElementBuffer(const GLuint buffer) : M_buffer{buffer}, M_elements{}
  {
    std::cerr << "Constructing element buffer\n";
    
    if (buffer != 0U)
      return;

    glGenBuffers(1, &M_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, M_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, M_elements.size(), M_elements.data(), GL_STATIC_DRAW);
  }

  ElementBuffer(ElementBuffer &&other) noexcept : M_buffer{other.M_buffer}, M_elements{other.M_elements}
  {
    std::cerr << "Move constructing element buffer\n";
    other.M_buffer = 0U;
  }

  ElementBuffer &operator=(ElementBuffer &&other) noexcept
  {
    std::cerr << "Move assigning element buffer\n";

    if (this != &other)
    {
      glDeleteBuffers(1, &M_buffer);
      this->M_elements = other.M_elements;
      this->M_buffer = other.M_buffer;
      other.M_buffer = 0U;
    }
    return *this;
  }

  ElementBuffer(const ElementBuffer &) = delete;
  ElementBuffer &operator=(const ElementBuffer &) = delete;

  ~ElementBuffer()
  {
    std::cerr << "Destructing element buffer\n";
    glDeleteBuffers(1, &M_buffer);
  }

  void Bind() const
  {
    assert(M_buffer != 0U);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, M_buffer);
  }

  void Unbind() const
  {
    assert(M_buffer != 0U);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0U);
  }

  void Copy(const std::array<T, N>& elements)
  {
    M_elements = elements;
  }

private:
  GLuint M_buffer;
  std::array<T, N> M_elements;
};
