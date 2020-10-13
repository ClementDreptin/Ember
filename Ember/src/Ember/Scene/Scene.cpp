#include "ebpch.h"
#include "Scene.h"

#include "Ember/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace Ember {
	Scene::Scene() {}

	Scene::~Scene() {}

	void Scene::OnUpdate(Timestep ts) {
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group) {
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawQuad(transform, sprite.Color);
		}
	}

	entt::entity Scene::CreateEntity() {
		return m_Registry.create();
	}
}