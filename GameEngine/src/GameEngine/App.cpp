#include "gepch.h"
#include "App.h"

#include "GameEngine/Log.h"

#include <GLFW/glfw3.h>

namespace GameEngine {
	#define BIND_EVENT_FN(x) std::bind(&App::x, this, std::placeholders::_1)

	App::App() {
		m_Window = std::unique_ptr<Window>(Window::create());
		m_Window->setEventCallback(BIND_EVENT_FN(onEvent));
	}

	App::~App() {

	}

	void App::onEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

		GE_CORE_TRACE("{0}", e);
	}

	void App::run() {
		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->onUpdate();
		}
	}

	bool App::onWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
}