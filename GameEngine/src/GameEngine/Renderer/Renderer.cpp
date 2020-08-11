#include "gepch.h"
#include "Renderer.h"

namespace GameEngine {
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::beginScene(OrthographicCamera& camera) {
		m_SceneData->viewProjectionMatrix = camera.getViewProjectionMatrix();
	}

	void Renderer::endScene() {}

	void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray> vertexArray) {
		shader->bind();
		shader->uploadUniformMat4("u_ViewProjection", m_SceneData->viewProjectionMatrix);

		vertexArray->bind();
		RenderCommand::drawIndexed(vertexArray);
	}
}