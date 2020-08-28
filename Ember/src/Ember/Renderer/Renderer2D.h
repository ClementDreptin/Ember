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

		// Vec2 for position - no rotation - color
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);

		// Vec3 for position - no rotation - color
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		// Vec2 for position - rotation - color
		static void DrawQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color);

		// Vec3 for position - rotation - color
		static void DrawQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const glm::vec4& color);

		// Vec2 for position - no rotation - texture
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);

		// Vec3 for position - rotation - texture
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);

		// Vec2 for position - rotation - texture
		static void DrawQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture);

		// Vec3 for position - rotation - texture
		static void DrawQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture);
	};
}