#pragma once

#include "entt.hpp"

namespace Ember {
	class Scene {
	public:
		Scene();
		~Scene();
	private:
		entt::registry m_Registry;
	};
}