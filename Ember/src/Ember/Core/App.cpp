#include "ebpch.h"
#include "App.h"

#include "Ember/Core/Log.h"

#include "Ember/Renderer/Renderer.h"

#include "Input.h"

#include <GLFW/glfw3.h>

namespace Ember {
	App* App::s_Instance = nullptr;

	App::App() {
		EB_PROFILE_FUNCTION();

		EB_CORE_ASSERT(!s_Instance, "App already exists!");
		s_Instance = this;

		m_Window = Scope<Window>(Window::Create());
		m_Window->SetEventCallback(EB_BIND_EVENT_FN(App::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	App::~App() {
		EB_PROFILE_FUNCTION();
	}

	void App::PushLayer(Layer* layer) {
		EB_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void App::PushOverlay(Layer* layer) {
		EB_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void App::OnEvent(Event& e) {
		EB_PROFILE_FUNCTION();

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
		EB_PROFILE_FUNCTION();

		while (m_Running) {
			EB_PROFILE_SCOPE("RunLoop");

			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized) {
				{
					EB_PROFILE_SCOPE("LayerStack OnUpdate");
					for (Layer* layer : m_LayerStack) {
						layer->OnUpdate(timestep);
					}
				}

				m_ImGuiLayer->Begin();
				{
					EB_PROFILE_SCOPE("LayerStack OnImGuiRender");
					for (Layer* layer : m_LayerStack) {
						layer->OnImGuiRender();
					}
				}
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();
		}
	}

	bool App::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	bool App::OnWindowResize(WindowResizeEvent& e) {
		EB_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}