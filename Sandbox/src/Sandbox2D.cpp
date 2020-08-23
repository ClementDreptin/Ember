#include <GameEngine.h>
#include "Sandbox2D.h"

#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) {

}

void Sandbox2D::onAttach() {
	// Square - START
	m_SquareVertexArray = GameEngine::VertexArray::create();
	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	GameEngine::Ref<GameEngine::VertexBuffer> squareVertexBuffer;
	squareVertexBuffer = GameEngine::VertexBuffer::create(squareVertices, sizeof(squareVertices));
	GameEngine::BufferLayout squareLayout = {
		{ GameEngine::ShaderDataType::Float3, "a_Position" }	
	};
	squareVertexBuffer->setLayout(squareLayout);
	m_SquareVertexArray->addVertexBuffer(squareVertexBuffer);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	GameEngine::Ref<GameEngine::IndexBuffer> squareIndexBuffer;
	squareIndexBuffer = GameEngine::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVertexArray->setIndexBuffer(squareIndexBuffer);

	m_FlatColorShader = GameEngine::Shader::create("assets/shaders/FlatColor.glsl");
	// Square - END
}

void Sandbox2D::onDetach() {}

void Sandbox2D::onUpdate(GameEngine::Timestep timestep) {
	m_CameraController.onUpdate(timestep);

	GameEngine::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	GameEngine::RenderCommand::clear();

	GameEngine::Renderer::beginScene(m_CameraController.getCamera());

	std::dynamic_pointer_cast<GameEngine::OpenGLShader>(m_FlatColorShader)->bind();
	std::dynamic_pointer_cast<GameEngine::OpenGLShader>(m_FlatColorShader)->uploadUniformFloat4("u_Color", m_SquareColor);

	GameEngine::Renderer::submit(m_FlatColorShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	GameEngine::Renderer::endScene();
}

void Sandbox2D::onImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::onEvent(GameEngine::Event& event) {
	m_CameraController.onEvent(event);
}