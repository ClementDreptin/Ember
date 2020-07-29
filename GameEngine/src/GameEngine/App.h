#pragma once

#include "Core.h"

namespace GameEngine {
	class GE_API App {
	public:
		App();
		virtual ~App();

		void run();
	};

	// To be defined in a Client
	App* CreateApp();
}
