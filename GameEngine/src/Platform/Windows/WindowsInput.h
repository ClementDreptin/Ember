#pragma once

#include "GameEngine/Core/Input.h"

namespace GameEngine {
	class WindowsInput : public Input {
	protected:
		virtual bool isKeyPressedImpl(int keyCode) override;

		virtual bool isMouseButtonPressedImpl(int button) override;
		virtual float getMouseXImpl() override;
		virtual float getMouseYImpl() override;
		virtual std::pair<float, float> getMousePositionImpl() override;
	};
}