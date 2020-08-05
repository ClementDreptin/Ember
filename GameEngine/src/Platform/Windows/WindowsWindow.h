#pragma once

#include "GameEngine/Window.h"
#include "GameEngine/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace GameEngine {
	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void onUpdate() override;

		inline unsigned int getWidth() const override { return m_Data.width; }
		inline unsigned int getHeight() const override { return m_Data.height; }

		// Window attributes
		inline void setEventCallback(const EventCallbackFn& callback) override { m_Data.eventCallback = callback; }
		void setVSync(bool enabled) override;
		bool isVSync() const override;

		inline virtual void* getNativeWindow() const { return m_Window; }
	private:
		virtual void init(const WindowProps& props);
		virtual void shutdown();
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData {
			std::string title;
			unsigned int width, height;
			bool VSync;

			EventCallbackFn eventCallback;
		};

		WindowData m_Data;
	};
}