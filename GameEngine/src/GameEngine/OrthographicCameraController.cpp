#include "gepch.h"
#include "OrthographicCameraController.h"

#include "GameEngine/Input.h"
#include "GameEngine/KeyCodes.h"

namespace GameEngine {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation) 
		: m_AspectRatio(aspectRatio),
		  m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
		  m_Rotation(rotation) {
		
	}

	void OrthographicCameraController::onUpdate(Timestep timestep) {
		if (Input::isKeyPressed(GE_KEY_A)) {
			m_CameraPosition.x -= m_CameraTranslationSpeed * timestep;
		}
		else if (Input::isKeyPressed(GE_KEY_D)) {
			m_CameraPosition.x += m_CameraTranslationSpeed * timestep;
		}

		if (Input::isKeyPressed(GE_KEY_W)) {
			m_CameraPosition.y -= m_CameraTranslationSpeed * timestep;
		}
		else if (Input::isKeyPressed(GE_KEY_S)) {
			m_CameraPosition.y += m_CameraTranslationSpeed * timestep;
		}

		if (m_Rotation) {
			if (Input::isKeyPressed(GE_KEY_Q)) {
				m_CameraRotation -= m_CameraRotationSpeed * timestep;
			}
			else if (Input::isKeyPressed(GE_KEY_E)) {
				m_CameraRotation += m_CameraRotationSpeed * timestep;
			}

			m_Camera.setRotation(m_CameraRotation);
		}

		m_Camera.setPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::onEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<MouseScrolledEvent>(GE_BIND_EVENT_FN(OrthographicCameraController::onMouseScrolled));
		dispatcher.dispatch<WindowResizeEvent>(GE_BIND_EVENT_FN(OrthographicCameraController::onWindowResized));
	}

	bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e) {
		m_ZoomLevel -= e.getYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.setProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::onWindowResized(WindowResizeEvent& e) {
		m_AspectRatio = (float)e.getWidth() / e.getHeight();
		m_Camera.setProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}
}