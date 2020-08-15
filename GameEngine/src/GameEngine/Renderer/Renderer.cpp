#include "gepch.h"
#include "Renderer.h"

namespace GameEngine {
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::beginScene(OrthographicCamera& camera) {
		m_SceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();
	}

	void Renderer::endScene() {}

	void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray> vertexArray, const glm::mat4& transform) {
		shader->bind();
		shader->uploadUniformMat4("u_ViewProjection", m_SceneData->viewProjectionMatrix);
		shader->uploadUniformMat4("u_Transform", transform);

		vertexArray->bind();
		RenderCommand::drawIndexed(vertexArray);
	}
}