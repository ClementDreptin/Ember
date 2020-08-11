#pragma once

#include "GameEngine/Core.h"
#include "GameEngine/Core/Timestep.h"
#include "GameEngine/Events/Event.h"

namespace GameEngine {
	class Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate(Timestep timestep) {}
		virtual void onImGuiRender() {}
		virtual void onEvent(Event& event) {}

		inline const std::string& getName() { return m_DebugName; }
		
	protected:
		std::string m_DebugName;
	};
}