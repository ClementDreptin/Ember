#pragma once

#include "Core.h"

#include "Window.h"
#include "GameEngine/Core/LayerStack.h"
#include "GameEngine/Events/Event.h"
#include "GameEngine/Events/AppEvent.h"

#include "GameEngine/Core/Timestep.h"

#include "GameEngine/ImGui/ImGuiLayer.h"

namespace GameEngine {
	class App {
	public:
		App();
		virtual ~App();

		void run();

		void onEvent(Event&);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);

		inline static App& get() { return *s_Instance; }
		inline Window& getWindow() { return *m_Window; }
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

		static App* s_Instance;

		float m_LastFrameTime = 0.0f;

		bool onWindowClose(WindowCloseEvent& e);
		bool onWindowResize(WindowResizeEvent& e);
	};

	// To be defined in a Client
	App* CreateApp();
}
