#pragma once

#include <Ember.h>
#include "ParticleSystem.h"

class Sandbox2D : public Ember::Layer {
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Ember::Timestep timestep) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Ember::Event& event) override;
private:
	Ember::OrthographicCameraController m_CameraController;

	// Temp
	Ember::Ref<Ember::Shader> m_FlatColorShader;
	Ember::Ref<Ember::VertexArray> m_SquareVertexArray;

	Ember::Ref<Ember::Texture2D> m_CheckerboardTexture;
	Ember::Ref<Ember::Texture2D> m_SpriteSheet;
	Ember::Ref<Ember::SubTexture2D> m_TextureStairs, m_TextureBarrel, m_TextureTree;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;
};