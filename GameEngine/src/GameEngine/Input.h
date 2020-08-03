#pragma once

#include "GameEngine/Core.h"

namespace GameEngine {
	class GE_API Input {
	public:
		inline static bool isKeyPressed(int keyCode) { return s_Instance->isKeyPressedImpl(keyCode); }

		inline static bool isMouseButtonPressed(int button) { return s_Instance->isMouseButtonPressedImpl(button); }
		inline static float getMouseX() { return s_Instance->getMouseXImpl(); }
		inline static float getMouseY() { return s_Instance->getMouseYImpl(); }
		inline static std::pair<float, float> getMousePosition() { return s_Instance->getMousePositionImpl(); }
	protected:
		virtual bool isKeyPressedImpl(int KeyCode) = 0;

		virtual bool isMouseButtonPressedImpl(int button) = 0;
		virtual float getMouseXImpl() = 0;
		virtual float getMouseYImpl() = 0;
		virtual std::pair<float, float> getMousePositionImpl() = 0;
	private:
		static Input* s_Instance;
	};
}