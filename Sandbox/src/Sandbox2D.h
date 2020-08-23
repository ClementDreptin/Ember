#pragma once
#include <GameEngine.h>

class Sandbox2D : public GameEngine::Layer {
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void onAttach() override;
	virtual void onDetach() override;

	void onUpdate(GameEngine::Timestep timestep) override;
	virtual void onImGuiRender() override;
	void onEvent(GameEngine::Event& event) override;
private:
	GameEngine::OrthographicCameraController m_CameraController;

	// Temp
	GameEngine::Ref<GameEngine::Shader> m_FlatColorShader;
	GameEngine::Ref<GameEngine::VertexArray> m_SquareVertexArray;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};