#include <GameEngine.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public GameEngine::Layer {
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) {
		m_VertexArray = GameEngine::VertexArray::create();

		// Triangle - START
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		GameEngine::Ref<GameEngine::VertexBuffer> triangleVertexBuffer;
		triangleVertexBuffer = GameEngine::VertexBuffer::create(vertices, sizeof(vertices));
		GameEngine::BufferLayout layout = {
			{ GameEngine::ShaderDataType::Float3, "a_Position" },
			{ GameEngine::ShaderDataType::Float4, "a_Color" }
		};
		triangleVertexBuffer->setLayout(layout);
		m_VertexArray->addVertexBuffer(triangleVertexBuffer);

		uint32_t triangleIndices[3] = { 0, 1, 2 };
		GameEngine::Ref<GameEngine::IndexBuffer> triangleIndexBuffer;
		triangleIndexBuffer = GameEngine::IndexBuffer::create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t));
		m_VertexArray->setIndexBuffer(triangleIndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main() {
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = GameEngine::Shader::create(vertexSrc, fragmentSrc);
		// Triangle - END

		// Square - START
		m_SquareVertexArray = GameEngine::VertexArray::create();
		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		GameEngine::Ref<GameEngine::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer = GameEngine::VertexBuffer::create(squareVertices, sizeof(squareVertices));
		GameEngine::BufferLayout squareLayout = {
			{ GameEngine::ShaderDataType::Float3, "a_Position" },
			{ GameEngine::ShaderDataType::Float2, "a_TextCoord" }
		};
		squareVertexBuffer->setLayout(squareLayout);
		m_SquareVertexArray->addVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		GameEngine::Ref<GameEngine::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer = GameEngine::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVertexArray->setIndexBuffer(squareIndexBuffer);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main() {
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main() {
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = GameEngine::Shader::create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
		// Square - END

		m_TextureShader = GameEngine::Shader::create("assets/shaders/Texture.glsl");

		m_Texture = GameEngine::Texture2D::create("assets/textures/checkerboard.png");
		m_ChernoLogoTexture = GameEngine::Texture2D::create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<GameEngine::OpenGLShader>(m_TextureShader)->bind();
		std::dynamic_pointer_cast<GameEngine::OpenGLShader>(m_TextureShader)->uploadUniformInt("u_Texture", 0);
	}

	void onUpdate(GameEngine::Timestep timestep) override {
		if (GameEngine::Input::isKeyPressed(GE_KEY_LEFT)) {
			m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
		} else if (GameEngine::Input::isKeyPressed(GE_KEY_RIGHT)) {
			m_CameraPosition.x += m_CameraMoveSpeed * timestep;
		}

		if (GameEngine::Input::isKeyPressed(GE_KEY_UP)) {
			m_CameraPosition.y -= m_CameraMoveSpeed * timestep;
		} else if (GameEngine::Input::isKeyPressed(GE_KEY_DOWN)) {
			m_CameraPosition.y += m_CameraMoveSpeed * timestep;
		}

		if (GameEngine::Input::isKeyPressed(GE_KEY_A)) {
			m_CameraRotation -= m_CameraRotationSpeed * timestep;
		} else if (GameEngine::Input::isKeyPressed(GE_KEY_D)) {
			m_CameraRotation += m_CameraRotationSpeed * timestep;
		}


		GameEngine::RenderCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		GameEngine::RenderCommand::clear();

		m_Camera.setPosition(m_CameraPosition);
		m_Camera.setRotation(m_CameraRotation);

		GameEngine::Renderer::beginScene(m_Camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<GameEngine::OpenGLShader>(m_FlatColorShader)->bind();
		std::dynamic_pointer_cast<GameEngine::OpenGLShader>(m_FlatColorShader)->uploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 10; x++) {
				glm::vec3 position(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;
				GameEngine::Renderer::submit(m_FlatColorShader, m_SquareVertexArray, transform);
			}
		}

		m_Texture->bind();
		GameEngine::Renderer::submit(m_TextureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoLogoTexture->bind();
		GameEngine::Renderer::submit(m_TextureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//GameEngine::Renderer::submit(m_Shader, m_VertexArray);

		GameEngine::Renderer::endScene();
	}

	virtual void onImGuiRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void onEvent(GameEngine::Event& event) override {}
private:
	GameEngine::Ref<GameEngine::Shader> m_Shader;
	GameEngine::Ref<GameEngine::VertexArray> m_VertexArray;

	GameEngine::Ref<GameEngine::Shader> m_FlatColorShader, m_TextureShader;
	GameEngine::Ref<GameEngine::VertexArray> m_SquareVertexArray;

	GameEngine::Ref<GameEngine::Texture2D> m_Texture, m_ChernoLogoTexture;

	GameEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;

	float m_CameraRotationSpeed = 1.0f;
	float m_CameraMoveSpeed = 1.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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