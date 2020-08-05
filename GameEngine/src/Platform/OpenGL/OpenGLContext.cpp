#include "gepch.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace GameEngine {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {
		GE_CORE_ASSERT(windowHandle, "windowHandle is null!");
	}

	void OpenGLContext::init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GE_CORE_ASSERT(status, "Failed to initialize Glad!");
	}

	void OpenGLContext::swapBuffers() {
		glfwSwapBuffers(m_WindowHandle);
	}
}