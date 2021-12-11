#include "stdafx.h"
#include "Mp.h"

Mp::Mp()
{

}

Mp::~Mp()
{

}

bool Mp::Start()
{
	m_mpBar.Init("Assets/sprite/MPbar.DDS", 500.0f, 800.0f);
	m_mpBar.SetPosition(Vector3(-520.0f, -390.0f, 0.0f));
	m_mpBar.Update();
	m_mpFrame.Init("Assets/sprite/MPFrame.DDS", 600.0f, 600.0f);
	m_mpFrame.SetPosition(Vector3(-560.0f, -340.0f, 0.0f));
	m_mpFrame.Update();

	return true;
}

void Mp::Update() 
{
	Cut();
	Heal();
	m_mpBar.Update();
	m_mpFrame.Update();
}

void Mp::Cut()
{
	float x = m_mp / 100;
	m_mpBar.SetIsDisplayRestrictionRightSide(true);
	m_mpBar.SetLimitedX(x);
}

void Mp::Heal()
{
	m_timer += g_gameTime->GetFrameDeltaTime();
	if (m_timer >= 1.0f) {
		m_mp += 1.0f;
		m_timer = 0.0f;
	}
}

void Mp::Render(RenderContext& rc) 
{
	m_mpBar.Draw(rc);
	m_mpFrame.Draw(rc);
}