#include "gepch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace GameEngine {
	struct Renderer2DStorage {
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> FlatColorShader;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::init() {
		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray = VertexArray::create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Ref<VertexBuffer> squareVertexBuffer;
		squareVertexBuffer = VertexBuffer::create(squareVertices, sizeof(squareVertices));
		BufferLayout squareLayout = {
			{ GameEngine::ShaderDataType::Float3, "a_Position" }
		};
		squareVertexBuffer->setLayout(squareLayout);
		s_Data->QuadVertexArray->addVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIndexBuffer;
		squareIndexBuffer = IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_Data->QuadVertexArray->setIndexBuffer(squareIndexBuffer);

		s_Data->FlatColorShader = Shader::create("assets/shaders/FlatColor.glsl");
	}

	void Renderer2D::shutdown() {
		delete s_Data;
	}

	void Renderer2D::beginScene(const OrthographicCamera& camera) {
		s_Data->FlatColorShader->bind();
		s_Data->FlatColorShader->setMat4("u_ViewProjection", camera.getViewProjectionMatrix());
	}

	void Renderer2D::endScene() {

	}

	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
		drawQuad({position.x, position.y, 0.0f}, size, color);
	}

	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		s_Data->FlatColorShader->bind();
		s_Data->FlatColorShader->setFloat4("u_Color", color);

		glm::mat4 transform = 
			glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		s_Data->FlatColorShader->setMat4("u_Transform", transform);

		s_Data->QuadVertexArray->bind();
		RenderCommand::drawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer2D::drawQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color) {
		drawQuad({ position.x, position.y, 0.0f }, rotation, size, color);
	}

	void Renderer2D::drawQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const glm::vec4& color) {
		s_Data->FlatColorShader->bind();
		s_Data->FlatColorShader->setFloat4("u_Color", color);

		glm::mat4 transform =
			glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1)) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->FlatColorShader->setMat4("u_Transform", transform);

		s_Data->QuadVertexArray->bind();
		RenderCommand::drawIndexed(s_Data->QuadVertexArray);
	}
}