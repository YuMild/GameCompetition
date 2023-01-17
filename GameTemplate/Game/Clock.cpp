#include "stdafx.h"
#include "Clock.h"

#include "Game.h"

namespace
{
	const float SQUARE_WIDTH	= 300.0f;
	const float SQUARE_HEIGHT	= 300.0f;
}

Clock::Clock()
{

}

Clock::~Clock()
{

}

bool Clock::Start() 
{
	m_clockCenterPosition = { -740.0f, 330.0f, 0.0f };

	m_clockBackGround.Init("Assets/sprite/Clock/ClockBackGround.DDS", SQUARE_WIDTH, SQUARE_HEIGHT);
	m_clockBackGround.SetPosition(m_clockCenterPosition);
	m_clockBackGround.Update();
	m_clockMinuteHund.Init("Assets/sprite/Clock/ClockMinuteHund.DDS", SQUARE_WIDTH, SQUARE_HEIGHT);
	m_clockMinuteHund.SetPosition(m_clockCenterPosition);
	m_clockMinuteHund.Update();
	m_clockSecondHund.Init("Assets/sprite/Clock/ClockSecondHund.DDS", SQUARE_WIDTH, SQUARE_HEIGHT);
	m_clockSecondHund.SetPosition(m_clockCenterPosition);
	m_clockSecondHund.Update();
	m_clockFrame.Init("Assets/sprite/Clock/ClockFrame.DDS", SQUARE_WIDTH, SQUARE_HEIGHT);
	m_clockFrame.SetPosition(m_clockCenterPosition);
	m_clockFrame.Update();
	m_clockFrameGray.Init("Assets/sprite/Clock/ClockFrameGray.DDS", SQUARE_WIDTH, SQUARE_HEIGHT);
	m_clockFrameGray.SetPosition(m_clockCenterPosition);
	m_clockFrameGray.Update();

	m_game = FindGO<Game>("game");

	return true;
}

void Clock::Update() 
{
	if (m_game->GetManageState() == 0)//¶‘¶Žž
	{
		m_clockBackGround.Update();
		m_clockMinuteHund.Update();
		m_clockSecondHund.Update();
		m_clockFrame.Update();
		Rotation();
	}
	else
	{
		m_clockFrameGray.Update();
	}
}

void Clock::Render(RenderContext& rc)
{
	m_clockBackGround.Draw(rc);
	m_clockFrameGray.Draw(rc);
	m_clockMinuteHund.Draw(rc);
	m_clockSecondHund.Draw(rc);

	if (m_game->GetManageState() == 0)//¶‘¶Žž
	{
		m_clockFrame.Draw(rc);
	}
}

void Clock::Rotation()
{
	m_timer += g_gameTime->GetFrameDeltaTime();
	m_secondRotation = m_timer * 30.0f;
	m_minuteRotation = m_timer * 2.5;
	m_secondHundRotation.SetRotationDegZ(-m_secondRotation);
	m_minuteHundRotation.SetRotationDegZ(-m_minuteRotation);
	m_clockSecondHund.SetRotation(m_secondHundRotation);
	m_clockMinuteHund.SetRotation(m_minuteHundRotation);
}