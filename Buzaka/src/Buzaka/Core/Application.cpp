#include "pch/bzpch.h"

#include "Application.h"
#include "Log.h"

#include <GLFW/glfw3.h>

namespace Buzaka {

#define BIND_EVENT_FUNC(func) std::bind(&func, this, std::placeholders::_1)

    Application::Application() {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));
    };

    Application::~Application() = default;

    void Application::OnEvent(Event& event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Application::OnWindowClose));

//        BZ_CORE_TRACE("{0}", event);

        for (Layer* layer : std::ranges::reverse_view(m_LayerStack)) {
          layer->OnEvent(event);
          if (event.IsHandled())
              break;
        };
    }

    void Application::Run() {
        while (m_Running) {
            for (Layer* layer : m_LayerStack)
                layer->OnUpdate();

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent &event) {
        m_Running = false;
        return true;
    }

    void Application::PushLayer(Layer *layer) {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer *overlay) {
        m_LayerStack.PushOverlay(overlay);
    }
}
