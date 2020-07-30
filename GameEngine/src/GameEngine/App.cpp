#include "gepch.h"
#include "App.h"

#include "GameEngine/Events/AppEvent.h"
#include "GameEngine/Log.h"

namespace GameEngine {
	App::App() {

	}

	App::~App() {

	}

	void App::run() {
		WindowResizeEvent e(1280, 720);
		GE_TRACE(e);

		for (;;) {

		}
	}
}