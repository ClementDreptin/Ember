#pragma once

#include "GameEngine/Renderer/OrthographicCamera.h"
#include "GameEngine/Core/Timestep.h"

#include "GameEngine/Events/AppEvent.h"
#include "GameEngine/Events/MouseEvent.h"

namespace GameEngine {
	class OrthographicCameraController {
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void onUpdate(Timestep ts);
		void onEvent(Event& e);

		OrthographicCamera& getCamera() { return m_Camera; }
		const OrthographicCamera& getCamera() const { return m_Camera; }
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		bool m_Rotation = false;

		OrthographicCamera m_Camera;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;

		bool onMouseScrolled(MouseScrolledEvent& event);
		bool onWindowResized(WindowResizeEvent& event);
	};
}