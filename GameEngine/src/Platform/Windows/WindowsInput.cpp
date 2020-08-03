#include "gepch.h"
#include "WindowsInput.h"

#include "GameEngine/App.h"

#include <GLFW/glfw3.h>

namespace GameEngine {
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::isKeyPressedImpl(int keyCode) {
		auto window = static_cast<GLFWwindow*>(App::get().getWindow().getNativeWindow());
		auto state = glfwGetKey(window, keyCode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::isMouseButtonPressedImpl(int button) {
		auto window = static_cast<GLFWwindow*>(App::get().getWindow().getNativeWindow());
		auto state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	float WindowsInput::getMouseXImpl() {
		auto [x, y] = getMousePositionImpl();
		return x;
	}

	float WindowsInput::getMouseYImpl() {
		auto [x, y] = getMousePositionImpl();
		return y;
	}

	std::pair<float, float> WindowsInput::getMousePositionImpl() {
		auto window = static_cast<GLFWwindow*>(App::get().getWindow().getNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return { (float)xPos, (float)xPos };
	}
}