#include "pch.h"
#ifdef KAREN_PLATFORM_LINUX

#include "Karen/Core/App.h"
#include "Karen/Core/Input.h"
#include <GLFW/glfw3.h>

namespace Karen
{
  bool Input::isKeyPressed(Keyboard key)
  {
    auto* window = (GLFWwindow*)App::get()->getWindow().getNativeWindow();
    auto  status = glfwGetKey(window, (int)key);
    return (status == GLFW_PRESS || status == GLFW_REPEAT);
  }

  Vec2 Input::getMousePos()
  {
    auto* window = (GLFWwindow*)App::get()->getWindow().getNativeWindow();
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return Vec2((float)x, (float)y);
  }

  bool Input::isMouseButtonPressed(Mouse button)
  {
    auto* window = (GLFWwindow*)App::get()->getWindow().getNativeWindow();
    auto status = glfwGetMouseButton(window, (int)button);
    return (status == GLFW_PRESS);
  }

  bool Input::isKeyReleased(Keyboard key)
  {
    auto* window = (GLFWwindow*)App::get()->getWindow().getNativeWindow();
    auto status = glfwGetKey(window, (int)key);
    return status == GLFW_RELEASE;
  }

  bool Input::isMouseButtonReleased(Mouse button)
  {
    auto* window = (GLFWwindow*)App::get()->getWindow().getNativeWindow();
    auto status = glfwGetMouseButton(window, (int)button);
    return status == GLFW_RELEASE;
  }
}

#endif //KAREN_PLATFORM_LINUX