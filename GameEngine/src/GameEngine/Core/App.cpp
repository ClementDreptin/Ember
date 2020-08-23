#include "gepch.h"
#include "App.h"

#include "GameEngine/Core/Log.h"

#include "GameEngine/Renderer/Renderer.h"

#include "Input.h"

#include <GLFW/glfw3.h>

namespace GameEngine {
	App* App::s_Instance = nullptr;

	App::App() {
		GE_CORE_ASSERT(!s_Instance, "App already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::create());
		m_Window->setEventCallback(GE_BIND_EVENT_FN(App::onEvent));

		Renderer::init();

		m_ImGuiLayer = new ImGuiLayer();
		pushOverlay(m_ImGuiLayer);
	}

	App::~App() {

	}

	void App::pushLayer(Layer* layer) {
		m_LayerStack.pushLayer(layer);
		layer->onAttach();
	}

	void App::pushOverlay(Layer* layer) {
		m_LayerStack.pushOverlay(layer);
		layer->onAttach();
	}

	void App::onEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(GE_BIND_EVENT_FN(App::onWindowClose));
		dispatcher.dispatch<WindowResizeEvent>(GE_BIND_EVENT_FN(App::onWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->onEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void App::run() {
		while (m_Running) {
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized) {
				for (Layer* layer : m_LayerStack) {
					layer->onUpdate(timestep);
				}
			}

			m_ImGuiLayer->begin();
			for (Layer* layer : m_LayerStack) {
				layer->onImGuiRender();
			}
			m_ImGuiLayer->end();

			m_Window->onUpdate();
		}
	}

	bool App::onWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	bool App::onWindowResize(WindowResizeEvent& e) {
		if (e.getWidth() == 0 || e.getHeight() == 0) {
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::onWindowResize(e.getWidth(), e.getHeight());

		return false;
	}
}