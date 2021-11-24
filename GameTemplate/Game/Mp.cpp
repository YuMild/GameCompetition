#include "stdafx.h"
#include "Mp.h"

Mp::Mp() {
}

Mp::~Mp() {
}

bool Mp::Start()
{
	m_mpFrame.Init("Assets/sprite/MPFrame.DDS", 600.0f, 600.0f);
	m_mpFrame.SetPosition(Vector3(-560.0f, -340.0f, 0.0f));
	m_mpFrame.Update();

	m_mpBar.Init("Assets/sprite/MPbar.DDS", 500.0f, 800.0f);
	m_mpBar.SetPosition(Vector3(-520.0f, -390.0f, 0.0f));
	m_mpBar.Update();

	return true;
}

void Mp::Update() 
{
	//float x = 1.0f / 3.0f * m_player->GetHP();
	//m_mpBar.SetIsDisplayRestrictionRightSide(true);
	//m_mpBar.SetLimitedX(x);

	m_mpBar.Update();
	m_mpFrame.Update();
}

void Mp::Render(RenderContext& rc) 
{
	m_mpBar.Draw(rc);
	m_mpFrame.Draw(rc);
}