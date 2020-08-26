#include <GameEngine.h>
#include "Sandbox2D.h"

#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {

}

void Sandbox2D::onAttach() {
	
}

void Sandbox2D::onDetach() {}

void Sandbox2D::onUpdate(GameEngine::Timestep timestep) {
	m_CameraController.onUpdate(timestep);

	GameEngine::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	GameEngine::RenderCommand::clear();

	GameEngine::Renderer2D::beginScene(m_CameraController.getCamera());
	GameEngine::Renderer2D::drawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	GameEngine::Renderer2D::drawQuad({ 0.5f, -0.5f }, 45, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	GameEngine::Renderer2D::endScene();
}

void Sandbox2D::onImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::onEvent(GameEngine::Event& event) {
	m_CameraController.onEvent(event);
}