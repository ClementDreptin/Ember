#include "ebpch.h"
#include "App.h"

#include "Ember/Core/Log.h"

#include "Ember/Renderer/Renderer.h"

#include "Input.h"

#include <GLFW/glfw3.h>

namespace Ember {
	App* App::s_Instance = nullptr;

	App::App() {
		EB_CORE_ASSERT(!s_Instance, "App already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(EB_BIND_EVENT_FN(App::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	App::~App() {

	}

	void App::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void App::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void App::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(EB_BIND_EVENT_FN(App::OnWindowClose));
		dispatcher.dispatch<WindowResizeEvent>(EB_BIND_EVENT_FN(App::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void App::Run() {
		while (m_Running) {
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized) {
				for (Layer* layer : m_LayerStack) {
					layer->OnUpdate(timestep);
				}
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) {
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool App::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	bool App::OnWindowResize(WindowResizeEvent& e) {
		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}