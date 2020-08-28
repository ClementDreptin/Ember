#pragma once

#include "Core.h"

#include "Window.h"
#include "Ember/Core/LayerStack.h"
#include "Ember/Events/Event.h"
#include "Ember/Events/AppEvent.h"

#include "Ember/Core/Timestep.h"

#include "Ember/ImGui/ImGuiLayer.h"

namespace Ember {
	class App {
	public:
		App();
		virtual ~App();

		void Run();

		void OnEvent(Event&);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static App& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

		static App* s_Instance;

		float m_LastFrameTime = 0.0f;

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	};

	// To be defined in a Client
	App* CreateApp();
}
