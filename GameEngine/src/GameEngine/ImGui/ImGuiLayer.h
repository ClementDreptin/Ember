#pragma once

#include "GameEngine/Core/Layer.h"
#include "GameEngine/Events/AppEvent.h"
#include "GameEngine/Events/KeyEvent.h"
#include "GameEngine/Events/MouseEvent.h"

namespace GameEngine {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onImGuiRender() override;

		void begin();
		void end();
	private:
		float m_Time = 0.0f;
	};
}