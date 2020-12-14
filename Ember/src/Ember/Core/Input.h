#pragma once

#include "Ember/Core/Core.h"

namespace Ember {
	class Input
	{
	public:
		static bool IsKeyPressed(int keyCode);

		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}
