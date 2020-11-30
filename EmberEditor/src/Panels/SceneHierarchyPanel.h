#pragma once

#include "Ember/Scene/Scene.h"
#include "Ember/Core/Log.h"
#include "Ember/Core/Core.h"
#include "Ember/Scene/Entity.h"

namespace Ember {
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;

		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	};
}