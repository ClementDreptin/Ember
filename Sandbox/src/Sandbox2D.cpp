#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"),
	  m_CameraController(1280.0f / 720.0f),
	  m_SquareColor({ 0.2f, 0.3f, 0.8f, 1.0f }) {}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Ember::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach() {}

void Sandbox2D::OnUpdate(Ember::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Ember::Renderer2D::ResetStats();

	Ember::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Ember::RenderCommand::Clear();

	static float rotation = 0.0f;
	rotation += ts * 50.0f;

	Ember::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Ember::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Ember::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Ember::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
	Ember::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, glm::radians(rotation), { 1.0f, 1.0f }, m_CheckerboardTexture, 20.0f);
	Ember::Renderer2D::EndScene();
	
	Ember::Renderer2D::BeginScene(m_CameraController.GetCamera());
	for (float y = -5.0f; y < 5; y += 0.5f)
	{
		for (float x = -5.0f; x < 5; x += 0.5f)
		{
			glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
			Ember::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
		}
	}
	Ember::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");

	auto stats = Ember::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox2D::OnEvent(Ember::Event& e)
{
	m_CameraController.OnEvent(e);
}