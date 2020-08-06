#include "gepch.h"
#include "App.h"

#include "GameEngine/Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace GameEngine {
	App* App::s_Instance = nullptr;

	App::App() {
		GE_CORE_ASSERT(!s_Instance, "App already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::create());
		m_Window->setEventCallback(GE_BIND_EVENT_FN(App::onEvent));

		m_ImGuiLayer = new ImGuiLayer();
		pushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->onEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void App::run() {
		while (m_Running) {
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->onUpdate();

			m_ImGuiLayer->begin();
			for (Layer* layer : m_LayerStack)
				layer->onImGuiRender();
			m_ImGuiLayer->end();

			m_Window->onUpdate();
		}
	}

	bool App::onWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
}