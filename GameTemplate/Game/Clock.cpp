#include "stdafx.h"
#include "Clock.h"

Clock::Clock()
{

}

Clock::~Clock()
{

}

bool Clock::Start() 
{
	m_clockCenterPosition = { -740.0f, 330.0f, 0.0f };

	m_clockBackGround.Init("Assets/sprite/ClockBackGround.DDS", 300.0f, 300.0f);
	m_clockBackGround.SetPosition(m_clockCenterPosition);
	m_clockBackGround.Update();
	m_clockMinuteHund.Init("Assets/sprite/ClockMinuteHund.DDS", 300.0f, 300.0f);
	m_clockMinuteHund.SetPosition(m_clockCenterPosition);
	m_clockMinuteHund.Update();
	m_clockSecondHund.Init("Assets/sprite/ClockSecondHund.DDS", 300.0f, 300.0f);
	m_clockSecondHund.SetPosition(m_clockCenterPosition);
	m_clockSecondHund.Update();
	m_clockFrame.Init("Assets/sprite/ClockFrame.DDS", 300.0f, 300.0f);
	m_clockFrame.SetPosition(m_clockCenterPosition);
	m_clockFrame.Update();

	return true;
}

void Clock::Update() 
{
	m_clockBackGround.Update();
	m_clockMinuteHund.Update();
	m_clockSecondHund.Update();
	m_clockFrame.Update();
	Rotation();
}

void Clock::Render(RenderContext& rc)
{
	m_clockBackGround.Draw(rc);
	m_clockMinuteHund.Draw(rc);
	m_clockSecondHund.Draw(rc);
	m_clockFrame.Draw(rc);
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