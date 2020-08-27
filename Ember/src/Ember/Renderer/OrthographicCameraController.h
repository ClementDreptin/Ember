#pragma once

#include "Ember/Renderer/OrthographicCamera.h"
#include "Ember/Core/Timestep.h"

#include "Ember/Events/AppEvent.h"
#include "Ember/Events/MouseEvent.h"

namespace Ember {
	class OrthographicCameraController {
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
			
		float GetZoomLevel() { return m_ZoomLevel; }
		void SetZoomLevel(float zoomLevel) { m_ZoomLevel = zoomLevel; }
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;

		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnWindowResized(WindowResizeEvent& event);
	};
}