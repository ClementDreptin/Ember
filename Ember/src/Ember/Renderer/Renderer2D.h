#pragma once
#include "OrthographicCamera.h"

#include "Texture.h"

namespace Ember {
	class Renderer2D {
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();

		// Vec2 for position - no rotation - color
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);

		// Vec3 for position - no rotation - color
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		// Vec2 for position - rotation - color
		static void DrawQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color);

		// Vec3 for position - rotation - color
		static void DrawQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const glm::vec4& color);

		// Vec2 for position - no rotation - texture - tiling factor - tint color
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		// Vec3 for position - rotation - texture - tiling factor - tint color
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		// Vec2 for position - rotation - texture - tiling factor - tint color
		static void DrawQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		// Vec3 for position - rotation - texture - tiling factor - tint color
		static void DrawQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

	private:
		static void PopulateQuadVertexBuffer(glm::mat4& transform, const glm::vec4& color, float textureIndex, float tilingFactor);
	};
}