#include <Ember.h>
#include <Ember/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public Ember::Layer
{
public:
	ExampleLayer() : Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{
		m_VertexArray = Ember::VertexArray::Create();

		// Triangle - START
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Ember::Ref<Ember::VertexBuffer> triangleVertexBuffer;
		triangleVertexBuffer = Ember::VertexBuffer::Create(vertices, sizeof(vertices));
		Ember::BufferLayout layout = {
			{ Ember::ShaderDataType::Float3, "a_Position" },
			{ Ember::ShaderDataType::Float4, "a_Color" }
		};
		triangleVertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(triangleVertexBuffer);

		uint32_t triangleIndices[3] = { 0, 1, 2 };
		Ember::Ref<Ember::IndexBuffer> triangleIndexBuffer;
		triangleIndexBuffer = Ember::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(triangleIndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
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

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Ember::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);
		// Triangle - END

		// Square - START
		m_SquareVertexArray = Ember::VertexArray::Create();
		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ember::Ref<Ember::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer = Ember::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		Ember::BufferLayout squareLayout = {
			{ Ember::ShaderDataType::Float3, "a_Position" },
			{ Ember::ShaderDataType::Float2, "a_TextCoord" }
		};
		squareVertexBuffer->SetLayout(squareLayout);
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ember::Ref<Ember::IndexBuffer> squareIndexBuffer;
		squareIndexBuffer = Ember::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Ember::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);
		// Square - END

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Ember::Texture2D::Create("assets/textures/checkerboard.png");
		m_ChernoLogoTexture = Ember::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Ember::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Ember::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Ember::Timestep timestep) override
	{
		m_CameraController.OnUpdate(timestep);

		Ember::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Ember::RenderCommand::Clear();

		Ember::Renderer::BeginScene(m_CameraController.GetCamera());

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Ember::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Ember::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				glm::vec3 position(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;
				Ember::Renderer::Submit(m_FlatColorShader, m_SquareVertexArray, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Ember::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind();
		Ember::Renderer::Submit(textureShader, m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//Ember::Renderer::submit(m_Shader, m_VertexArray);

		Ember::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Ember::Event& event) override
	{
		m_CameraController.OnEvent(event);
	}
private:
	Ember::ShaderLibrary m_ShaderLibrary;
	Ember::Ref<Ember::Shader> m_Shader;
	Ember::Ref<Ember::VertexArray> m_VertexArray;

	Ember::Ref<Ember::Shader> m_FlatColorShader;
	Ember::Ref<Ember::VertexArray> m_SquareVertexArray;

	Ember::Ref<Ember::Texture2D> m_Texture, m_ChernoLogoTexture;

	Ember::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Ember::App
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox() {}
};

Ember::App* Ember::CreateApp()
{
	return new Sandbox();
}