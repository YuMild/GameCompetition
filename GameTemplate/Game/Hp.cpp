#include "stdafx.h"
#include "Hp.h"

Hp::Hp() {

}
Hp::~Hp() {

}
bool Hp::Start() {
	m_hpInside.Init("Assets/sprite/HPInside.DDS", 500.0f, 800.0f);
	m_hpInside.SetPosition(Vector3(-520.0f, -390.0f, 0.0f));
	m_hpInside.Update();
	m_hpFrame.Init("Assets/sprite/HPFrame.DDS", 600.0f, 600.0f);
	m_hpFrame.SetPosition(Vector3(-560.0f, -340.0f, 0.0f));
	m_hpFrame.Update();

	return true;
}
void Hp::Update() {
	m_hpInside.Update();
	m_hpFrame.Update();
}
void Hp::Render(RenderContext& rc) {
	m_hpInside.Draw(rc);
	m_hpFrame.Draw(rc);
}