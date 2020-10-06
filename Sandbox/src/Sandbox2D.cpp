#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"),
	  m_CameraController(1280.0f / 720.0f),
	  m_SquareColor({ 0.2f, 0.3f, 0.8f, 1.0f }) {}

void Sandbox2D::OnAttach() {
	EB_PROFILE_FUNCTION();

	m_CheckerboardTexture = Ember::Texture2D::Create("assets/textures/Checkerboard.png");

	Ember::FrameBufferSpec spec;
	spec.Width = 1280;
	spec.Height = 720;
	m_FrameBuffer = Ember::FrameBuffer::Create(spec);
}

void Sandbox2D::OnDetach() {
	EB_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Ember::Timestep ts) {
	EB_PROFILE_SCOPE("CameraController::OnUpdate");

	m_CameraController.OnUpdate(ts);

	Ember::Renderer2D::ResetStats();

	{
		EB_PROFILE_SCOPE("Renderer Prep");
		m_FrameBuffer->Bind();
		Ember::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Ember::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		EB_PROFILE_SCOPE("Renderer Draw");
		Ember::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Ember::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Ember::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Ember::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		Ember::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, glm::radians(rotation), { 1.0f, 1.0f }, m_CheckerboardTexture, 20.0f);
		Ember::Renderer2D::EndScene();
		
		Ember::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5; y += 0.5f) {
			for (float x = -5.0f; x < 5; x += 0.5f) {
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Ember::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Ember::Renderer2D::EndScene();
		m_FrameBuffer->Unbind();
	}
}

void Sandbox2D::OnImGuiRender() {
	EB_PROFILE_FUNCTION();

	// Note: Switch this to true to enable dockspace
	static bool dockingEnabled = true;
	if (dockingEnabled) {
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen) {
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Exit")) Ember::App::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");

		auto stats = Ember::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

		uint32_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ 1280.0f, 720.0f });
		ImGui::End();

		ImGui::End();
	} else {
		ImGui::Begin("Settings");

		auto stats = Ember::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

		uint32_t textureID = m_CheckerboardTexture->GetRendererID();
		ImGui::Image((void*)textureID, ImVec2{ 256.0f, 256.0f });
		ImGui::End();
	}
}

void Sandbox2D::OnEvent(Ember::Event& e) {
	m_CameraController.OnEvent(e);
}