#pragma once

#include "Core.h"

#include "Window.h"
#include "GameEngine/LayerStack.h"
#include "Events/Event.h"
#include "GameEngine/Events/AppEvent.h"

#include "GameEngine/ImGui/ImGuiLayer.h"

// TEMPORARY
#include "GameEngine/Renderer/Shader.h"
#include "GameEngine/Renderer/Buffer.h"

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
		bool onWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static App* s_Instance;

		unsigned int m_VertexArray;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
	};

	// To be defined in a Client
	App* CreateApp();
}
