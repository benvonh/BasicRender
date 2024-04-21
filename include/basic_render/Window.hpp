#pragma once

#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "ElementBuffer.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

class Window final
{
public:
  Window(const char *title) : M_shader{}, M_vertexArray{}, M_vertexBuffer{}, M_elementBuffer{}, M_window{nullptr}
  {
    std::cerr << "Constructing window\n";

    glfwSetErrorCallback(Window::ErrorCallback);

    if (glfwInit() != GLFW_TRUE)
      throw std::runtime_error("Failed to initialise GLFW!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    M_window = glfwCreateWindow(1280, 720, title, nullptr, nullptr);

    if (M_window == nullptr)
      throw std::runtime_error("Failed to create window!");

    glfwMakeContextCurrent(M_window);

    if (!gladLoadGL())
      throw std::runtime_error("Failed to load GLAD!");

    glViewport(0, 0, 1280, 720);

    M_shader = Shader(R"(C:\Users\Ben\Source\BasicRender\res\Default.vert)",
                      R"(C:\Users\Ben\Source\BasicRender\res\Default.frag)");
    M_vertexArray = VertexArray(0U);
    M_vertexBuffer = VertexBuffer<GLfloat, 18UL>(0U);
    M_elementBuffer = ElementBuffer<GLuint, 9UL>(0U);
    M_vertexBuffer.Copy({
      -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,    // Lower left corner
      0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,     // Lower right corner
      0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  // Upper corner
      -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
      0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,  // Inner right
      0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f      // Inner down
    });
    M_elementBuffer.Copy({
      0, 3, 5, // Lower left triangle
      3, 2, 4, // Lower right triangle
      5, 4, 1  // Upper triangle
    });
    M_vertexArray.Link(M_vertexBuffer, 0U);

    M_vertexArray.Unbind();
    M_vertexBuffer.Unbind();
    M_elementBuffer.Unbind();
  }

  Window(Window &&) = delete;
  Window(const Window &) = delete;
  Window &operator=(Window &&) = delete;
  Window &operator=(const Window &) = delete;

  ~Window()
  {
    std::cerr << "Destructing window\n";
    glfwDestroyWindow(M_window);
    glfwTerminate();
  }

  bool Alive() const
  {
    return !glfwWindowShouldClose(M_window);
  }

  void Update() const
  {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    M_shader.Use();
    M_vertexArray.Bind();
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, nullptr);
    glfwSwapBuffers(M_window);
    glfwPollEvents();
  }

private:
  static void ErrorCallback(int code, const char *what)
  {
    std::cerr << "[Window] (" << code << ") " << what << std::endl;
  }

private:
  Shader M_shader;
  VertexArray M_vertexArray;
  VertexBuffer<GLfloat, 18UL> M_vertexBuffer;
  ElementBuffer<GLuint, 9UL> M_elementBuffer;
  GLFWwindow *M_window;
};
