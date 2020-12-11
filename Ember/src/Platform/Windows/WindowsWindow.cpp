#include "ebpch.h"
#include "WindowsWindow.h"
#include "Ember/Core/Log.h"

#include "Ember/Events/AppEvent.h"
#include "Ember/Events/MouseEvent.h"
#include "Ember/Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Ember {
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* desc)
	{
		EB_CORE_ERROR("GLFW Error code: ({0}) | {1}", error, desc);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.title = props.title;
		m_Data.width = props.width;
		m_Data.height = props.height;

		EB_CORE_INFO("Creating window \"{0}\" ({1}, {2})", props.title, props.width, props.height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			EB_CORE_ASSERT(success, "Could not initialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.width, (int)props.height, m_Data.title.c_str(), nullptr, nullptr);

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(window);
			windowData.width = width;
			windowData.height = height;

			WindowResizeEvent event(width, height);
			windowData.eventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			windowData.eventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					windowData.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					windowData.eventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					windowData.eventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keyCode)
		{
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keyCode);
			windowData.eventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					windowData.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					windowData.eventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			windowData.eventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y)
		{
			WindowData& windowData = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)x, (float)y);
			windowData.eventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}