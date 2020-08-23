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

		void onResize(float width, float height);

		OrthographicCamera& getCamera() { return m_Camera; }
		const OrthographicCamera& getCamera() const { return m_Camera; }
			
		float getZoomLevel() { return m_ZoomLevel; }
		void setZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; }
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;

		bool onMouseScrolled(MouseScrolledEvent& event);
		bool onWindowResized(WindowResizeEvent& event);
	};
}