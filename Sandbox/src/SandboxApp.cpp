#include <GameEngine.h>

class Sandbox : public GameEngine::App {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

GameEngine::App* GameEngine::CreateApp() {
	return new Sandbox();
}