#include "stdafx.h"
#include "BackGround.h"

bool BackGround::Start() {
	m_render.Init("Assets/modelData/stage.tkm");
	m_render.SetScale({ 1.5f,1.5f,1.5f });

	m_position.x = 0.0f;
	m_position.y = -70.0f;
	m_position.z = 0.0f;

	m_render.SetPosition(m_position);
	m_render.Update();

	m_physicsStaticObject.CreateFromModel(m_render.GetModel(), m_render.GetModel().GetWorldMatrix());

	return true;
}

void BackGround::Update() {

}

void BackGround::Render(RenderContext& rc) {
	m_render.Draw(rc);
}