#pragma once

#include "Core.h"

#include "Window.h"
#include "GameEngine/LayerStack.h"
#include "Events/Event.h"
#include "GameEngine/Events/AppEvent.h"

#include "GameEngine/ImGui/ImGuiLayer.h"

#include "GameEngine/Renderer/Shader.h"
#include "GameEngine/Renderer/Buffer.h"
#include "GameEngine/Renderer/VertexArray.h"

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

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVertexArray;
	};

	// To be defined in a Client
	App* CreateApp();
}
