#include "gepch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLShader.h"

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

	void Renderer2D::Shutdown() {
		delete s_Data;
	}

	void Renderer2D::beginScene(const OrthographicCamera& camera) {
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->uploadUniformMat4("u_ViewProjection", camera.getViewProjectionMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->uploadUniformMat4("u_Transform", glm::mat4(1.0f));
	}

	void Renderer2D::endScene() {

	}

	void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
		drawQuad({position.x, position.y, 0.0f}, size, color);
	}

	void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		std::dynamic_pointer_cast<OpenGLShader>(s_Data->FlatColorShader)->bind();
		std::dynamic_pointer_cast<GameEngine::OpenGLShader>(s_Data->FlatColorShader)->uploadUniformFloat4("u_Color", color);

		s_Data->QuadVertexArray->bind();
		RenderCommand::drawIndexed(s_Data->QuadVertexArray);
	}
}