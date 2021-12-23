#include "stdafx.h"
#include "Mp.h"

#include "Game.h"

Mp::Mp()
{

}

Mp::~Mp()
{

}

bool Mp::Start()
{
	m_mpBar.Init("Assets/sprite/Mp/MPbar.DDS", 500.0f, 800.0f);
	m_mpBar.SetPosition(Vector3(-520.0f, -390.0f, 0.0f));
	m_mpBar.Update();
	m_mpBarGray.Init("Assets/sprite/Mp/MPbarGray.DDS", 500.0f, 800.0f);
	m_mpBarGray.SetPosition(Vector3(-520.0f, -390.0f, 0.0f));
	m_mpBarGray.Update();
	m_mpFrame.Init("Assets/sprite/Mp/MPFrame.DDS", 600.0f, 600.0f);
	m_mpFrame.SetPosition(Vector3(-560.0f, -340.0f, 0.0f));
	m_mpFrame.Update();
	m_mpFrameGray.Init("Assets/sprite/Mp/MPFrameGray.DDS", 600.0f, 600.0f);
	m_mpFrameGray.SetPosition(Vector3(-560.0f, -340.0f, 0.0f));
	m_mpFrameGray.Update();

	m_game = FindGO<Game>("game");

	return true;
}

void Mp::Update() 
{
	Cut();
	Heal();
	m_mpBar.Update();
	m_mpFrame.Update();
	m_mpBarGray.Update();
	m_mpFrameGray.Update();
}

void Mp::Cut()
{
	if (m_game->GetManageState() == 0)
	{
		float x = m_mp / 100;
		m_mpBarGray.SetIsDisplayRestrictionRightSide(true);
		m_mpBarGray.SetLimitedX(x);
		m_mpBar.SetIsDisplayRestrictionRightSide(true);
		m_mpBar.SetLimitedX(x);
	}
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
	m_mpBarGray.Draw(rc);
	m_mpFrameGray.Draw(rc);
	if (m_game->GetManageState() == 0)
	{
		m_mpBar.Draw(rc);
		m_mpFrame.Draw(rc);
	}
}