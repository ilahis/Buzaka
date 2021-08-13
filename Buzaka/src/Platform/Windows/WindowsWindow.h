#pragma once

#include "pch/bzpch.h"
#include "Buzaka/Core/Window.h"

#include "GLFW/glfw3.h"

namespace Buzaka {

    class WindowsWindow : public Window {
    public:
        explicit WindowsWindow(const WindowProps& props);
        ~WindowsWindow() override;

        void OnUpdate() override;

        [[nodiscard]] inline unsigned int GetWidth() const override { return m_Data.Width; }
        [[nodiscard]] inline unsigned int GetHeight() const override { return m_Data.Height; }

        inline void SetEventCallback(const EventCallbackFunc& callbackFunc) override {
            m_Data.EventCallback = callbackFunc;
        }
        void SetVSync(bool enabled) override;
        [[nodiscard]] bool IsVSync() const override;
    private:
        void Init(const WindowProps& props);
        void Shutdown();

        GLFWwindow* m_Window;
        struct WindowData {
            std::string_view Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFunc EventCallback;
        };

        WindowData m_Data;
    };

}
