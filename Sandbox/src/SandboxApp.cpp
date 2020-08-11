#include <GameEngine.h>

#include "imgui/imgui.h"

class ExampleLayer : public GameEngine::Layer {
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) {
		m_VertexArray.reset(GameEngine::VertexArray::create());

		// Triangle - START
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<GameEngine::VertexBuffer> triangleVertexBuffer;
		triangleVertexBuffer.reset(GameEngine::VertexBuffer::create(vertices, sizeof(vertices)));
		GameEngine::BufferLayout layout = {
			{ GameEngine::ShaderDataType::Float3, "a_Position" },
			{ GameEngine::ShaderDataType::Float4, "a_Color" }
		};
		triangleVertexBuffer->setLayout(layout);
		m_VertexArray->addVertexBuffer(triangleVertexBuffer);

		uint32_t triangleIndices[3] = { 0, 1, 2 };
		std::shared_ptr<GameEngine::IndexBuffer> triangleIndexBuffer;
		triangleIndexBuffer.reset(GameEngine::IndexBuffer::create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));
		m_VertexArray->setIndexBuffer(triangleIndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_Shader.reset(new GameEngine::Shader(vertexSrc, fragmentSrc));
		// Triangle - END

		// Square - START
		m_SquareVertexArray.reset(GameEngine::VertexArray::create());
		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<GameEngine::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(GameEngine::VertexBuffer::create(squareVertices, sizeof(squareVertices)));
		GameEngine::BufferLayout squareLayout = {
			{ GameEngine::ShaderDataType::Float3, "a_Position" }
		};
		squareVertexBuffer->setLayout(squareLayout);
		m_SquareVertexArray->addVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<GameEngine::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(GameEngine::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->setIndexBuffer(squareIndexBuffer);

		std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main() {
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main() {
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new GameEngine::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
		// Square - END
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
		GameEngine::Renderer::submit(m_BlueShader, m_SquareVertexArray);
		GameEngine::Renderer::submit(m_Shader, m_VertexArray);
		GameEngine::Renderer::endScene();
	}

	virtual void onImGuiRender() override {}

	void onEvent(GameEngine::Event& event) override {}
private:
	std::shared_ptr<GameEngine::Shader> m_Shader;
	std::shared_ptr<GameEngine::VertexArray> m_VertexArray;

	std::shared_ptr<GameEngine::Shader> m_BlueShader;
	std::shared_ptr<GameEngine::VertexArray> m_SquareVertexArray;

	GameEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;

	float m_CameraRotationSpeed = 1.0f;
	float m_CameraMoveSpeed = 0.1f;
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