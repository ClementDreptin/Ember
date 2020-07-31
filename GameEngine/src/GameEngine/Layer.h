#pragma once

#include "GameEngine/Core.h"
#include "GameEngine/Events/Event.h"

namespace GameEngine {
	class GE_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onEvent(Event& event) {}

		inline const std::string& getName() { return m_DebugName; }
		
	protected:
		std::string m_DebugName;
	};
}