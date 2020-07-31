#include <GameEngine.h>

class ExampleLayer : public GameEngine::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void onUpdate() override {
		GE_INFO("ExampleLayer::onUpdate");
	}

	void onEvent(GameEngine::Event& event) override {
		GE_TRACE("{0}", event);
	}
};

class Sandbox : public GameEngine::App {
public:
	Sandbox() {
		pushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

GameEngine::App* GameEngine::CreateApp() {
	return new Sandbox();
}