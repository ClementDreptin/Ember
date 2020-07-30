#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "GameEngine/Events/AppEvent.h"
#include "Window.h"

namespace GameEngine {
	class GE_API App {
	public:
		App();
		virtual ~App();

		void run();

		void onEvent(Event&);
	private:
		bool onWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in a Client
	App* CreateApp();
}
