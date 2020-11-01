#include "SceneHierarchyPanel.h"

#include <imgui/imgui.h>

#include "Ember/Scene/Components.h"

namespace Ember {
	Ember::SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context) {
		SetContext(context);
	}

	void Ember::SceneHierarchyPanel::SetContext(const Ref<Scene>& context) {
		m_Context = context;
	}

	void Ember::SceneHierarchyPanel::OnImGuiRender() {
		ImGui::Begin("Scene Hierarchy");

		m_Context->m_Registry.each([&](auto entityID) {
			Entity entity{ entityID, m_Context.get() };
			DrawEntityNode(entity);
		});

		ImGui::End();
	}

	void Ember::SceneHierarchyPanel::DrawEntityNode(Entity entity) {
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
		bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());

		if (ImGui::IsItemClicked()) {
			m_SelectionContext = entity;
		}

		if (opened) {
			ImGui::TreePop();
		}
	}
}