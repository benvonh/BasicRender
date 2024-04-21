#include "basic_render/BasicRender.hpp"

int main()
{
  Window window("Basic Render");

  while (window.Alive())
    window.Update();
}
