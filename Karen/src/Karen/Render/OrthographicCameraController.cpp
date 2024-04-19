#include "Karen/Render/OrthographicCameraController.h"
#include "Karen/Core/ButtonsAndKeyCodes.h"
#include "Karen/Core/Events/AppEvents.h"
#include "Karen/Core/Events/Event.h"
#include "Karen/Core/Events/MouseEvents.h"
#include "Karen/Core/Input.h"
#include "Karen/Render/API/RenderCommands.h"


namespace Karen
{
  OrthographicCameraController::OrthographicCameraController(float aspect_ratio, const Vec4& initial)
    : m_aspect_ratio(aspect_ratio), m_initial(initial)
  {
     m_camera.setRect(m_aspect_ratio * m_initial.x, m_aspect_ratio * m_initial.y,
      m_initial.z, m_initial.w);
  }
  OrthographicCameraController::OrthographicCameraController(float left, float right, float bottom, float top)
  : m_camera(left, right, bottom, top)
  {
    m_initial.x = left;
    m_initial.y = right;
    m_initial.z = bottom;
    m_initial.w = top;
  } 
    
  void OrthographicCameraController::onUpdate(Timestep ts)
  {
    if(Input::isKeyPressed(Keyboard::A))
      move(Vec3(-1.0f, 0.0f, 0.0f) * (m_speed.x * ts));
    if(Input::isKeyPressed(Keyboard::D))
      move(Vec3(1.0f, 0.0f, 0.0f) * (m_speed.x * ts));
    if(Input::isKeyPressed(Keyboard::W))
      move(Vec3(0.0f, 1.0f, 0.0f) * (m_speed.x * ts));
    if(Input::isKeyPressed(Keyboard::S))
      move(Vec3(0.0f, -1.0f, 0.0f) * (m_speed.x * ts));
    if(Input::isKeyPressed(Keyboard::E))
      rotate(m_rotation_speed * ts);
    if(Input::isKeyPressed(Keyboard::Q))
      rotate(-m_rotation_speed * ts);
    m_camera.setZoom(m_zoom);
    m_camera.onUpdate(ts);
  }
  void OrthographicCameraController::onEvent(Event& e)
  {
    EventDispatcher dp(e); 
    KAREN_CORE_TRACE("Event sent to dispatcher [from Camera controler onEvent()] : {0}", e);
    dp.dispatch<WindowResizeEvent>(BIND_EVENT_FUNCTION(OrthographicCameraController::onWindowResizeEvent));
    dp.dispatch<MouseScrolledEvent>(BIND_EVENT_FUNCTION(OrthographicCameraController::onMouseScrollEvent));
  }

  bool OrthographicCameraController::onMouseScrollEvent(MouseScrolledEvent& e)
  {
    if(m_control_zoom_with_mouse_scroll)
    {
      zoom(-e.getYoffset());
    }
    return false;
  }
  
  bool OrthographicCameraController::onWindowResizeEvent(WindowResizeEvent& e)
  {
    m_aspect_ratio = (float)e.getWidth()/(float)e.getHeight();
    Vec4 current = m_initial;
    if(m_aspect_ratio > 1.0f)
    {
      current.x *= m_aspect_ratio;
      current.y *= m_aspect_ratio;
    }
    else
    {
      current.z = current.x / m_aspect_ratio;
      current.w = current.y / m_aspect_ratio;
    }
    setRect(current.x, current.y, current.z, current.w);
    //setRect(0.0f, m_aspect_ratio * e.getWidth(), 0.0f, e.getHeight());
    RenderCommands::setViewPort(0.0f, 0.0f, e.getWidth(), e.getHeight());
    KAREN_CORE_TRACE("ViewPort: ({0}, {1}, {2}, {3}), aspect_ratio: {4}", 0.0f, 0.0f, e.getWidth(), e.getHeight(), m_aspect_ratio);
    return true;
  }
}