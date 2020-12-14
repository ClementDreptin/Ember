#pragma once

#include "Ember/Core/Core.h"
#include "Ember/Core/Timestep.h"
#include "Ember/Events/Event.h"

namespace Ember {
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() { return m_DebugName; }
		
	protected:
		std::string m_DebugName;
	};
}
