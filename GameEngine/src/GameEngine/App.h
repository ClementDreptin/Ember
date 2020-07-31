#pragma once

#include "Core.h"

#include "Window.h"
#include "GameEngine/LayerStack.h"
#include "Events/Event.h"
#include "GameEngine/Events/AppEvent.h"

namespace GameEngine {
	class GE_API App {
	public:
		App();
		virtual ~App();

		void run();

		void onEvent(Event&);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
	private:
		bool onWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in a Client
	App* CreateApp();
}
