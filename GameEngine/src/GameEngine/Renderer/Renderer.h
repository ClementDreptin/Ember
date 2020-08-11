#pragma once

#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Shader.h"

namespace GameEngine {
	class Renderer {
	public:
		static void beginScene(OrthographicCamera& camera);
		static void endScene();

		static void submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray> vertexArray);

		static inline RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
	private:
		struct SceneData {
			glm::mat4 viewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}