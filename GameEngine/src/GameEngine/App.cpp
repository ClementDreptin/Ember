#include "gepch.h"
#include "App.h"

#include "GameEngine/Events/AppEvent.h"
#include "GameEngine/Log.h"

namespace GameEngine {
	App::App() {
		m_Window = std::unique_ptr<Window>(Window::create());
	}

	App::~App() {

	}

	void App::run() {
		while (m_Running) {
			m_Window->onUpdate();
		}
	}
}