#include "stdafx.h"
#include "TitleUi.h"

TitleUi::TitleUi() 
{
}

TitleUi::~TitleUi() 
{
}

bool TitleUi::Start()
{
	m_heart1.Init("Assets/sprite/Hp/HP1.DDS", 650.0f, 650.0f);
	m_heart2.Init("Assets/sprite/Hp/HP2.DDS", 460.0f, 460.0f);
	m_heart3.Init("Assets/sprite/Hp/HP3.DDS", 300.0f, 300.0f);
	m_fire1.Init("Assets/sprite/Magic/TypeFire.DDS", 380.0f, 380.0f);
	m_fire2.Init("Assets/sprite/Magic/TypeFire.DDS", 520.0f, 520.0f);
	m_water1.Init("Assets/sprite/Magic/TypeWater.DDS", 330.0f, 330.0f);
	m_water2.Init("Assets/sprite/Magic/TypeWater.DDS", 370.0f, 370.0f);
	m_wind1.Init("Assets/sprite/Magic/TypeWind.DDS", 550.0f, 550.0f);
	m_wind2.Init("Assets/sprite/Magic/TypeWind.DDS", 340.0f, 340.0f);
	m_shine1.Init("Assets/sprite/Magic/TypeShine.DDS", 360.0f, 360.0f);
	m_shine2.Init("Assets/sprite/Magic/TypeShine.DDS", 800.0f, 800.0f);

	return true;
}

void TitleUi::Update()
{
	if (g_pad[0]->IsTrigger(enButtonStart))
	{
		DeleteGO(this);
	}

	State();
	Timer();

	m_heart1Position = { 800.0f,-440.0f + m_upDown1,0.0f };
	m_heart1.SetPosition(m_heart1Position);
	m_heart1.Update();
	m_wind2Position = { -250.0f,-510.0f + m_upDown1,0.0f };
	m_wind2.SetPosition(m_wind2Position);
	m_wind2.Update();

	m_shine2Position = { -850.0f,-450.0f + m_upDown2,0.0f };
	m_shine2.SetPosition(m_shine2Position);
	m_shine2.Update();
	m_heart3Position = { 180.0f,-570.0f + m_upDown2,0.0f };
	m_heart3.SetPosition(m_heart3Position);
	m_heart3.Update();

	m_water1Position = { -420.0f,-560.0f + m_upDown3,0.0f };
	m_water1.SetPosition(m_water1Position);
	m_water1.Update();
	m_water2Position = { 180.0f,-490.0f + m_upDown3,0.0f };
	m_water2.SetPosition(m_water2Position);
	m_water2.Update();

	m_fire2Position = { -460.0f,-470.0f + m_upDown4,0.0f };
	m_fire2.SetPosition(m_fire2Position);
	m_fire2.Update();
	m_wind1Position = { 450.0f,-520.0f + m_upDown4,0.0f };
	m_wind1.SetPosition(m_wind1Position);
	m_wind1.Update();

	m_heart2Position = { -670.0f,-500.0f + m_upDown5,0.0f };
	m_heart2.SetPosition(m_heart2Position);
	m_heart2.Update();
	m_shine1Position = { -40.0f,-520.0f + m_upDown5,0.0f };
	m_shine1.SetPosition(m_shine1Position);
	m_shine1.Update();
	m_fire1Position = { 570.0f,-530.0f + m_upDown5,0.0f };
	m_fire1.SetPosition(m_fire1Position);
	m_fire1.Update();
}

void TitleUi::State()
{
	//タイマー1
	if (m_timer1 > 0.5f && m_timer1 < 0.7f)
	{
		m_upDown1 += 7.0f;
	}
	else if (m_timer1 > 0.8 && m_timer1 < 1.0f) 
	{
		m_upDown1 -= 7.0f;
	}
	else if (m_timer1 > 1.0f)
	{
		m_timer1 = 0;
		m_upDown1 = 0;
	}

	//タイマー2
	if (m_timer2 > 1.1f && m_timer2 < 1.3f)
	{
		m_upDown2 += 7.0f;
	}
	else if (m_timer2 > 1.4 && m_timer2 < 1.6f)
	{
		m_upDown2 -= 7.0f;
	}
	else if (m_timer2 > 1.6f)
	{
		m_timer2 = 0;
		m_upDown2 = 0;
	}

	//タイマー3
	if (m_timer3 > 1.7f && m_timer3 < 1.9f)
	{
		m_upDown3 += 7.0f;
	}
	else if (m_timer3 > 2.0 && m_timer3 < 2.2f)
	{
		m_upDown3 -= 7.0f;
	}
	else if (m_timer3 > 2.2f)
	{
		m_timer3 = 0;
		m_upDown3 = 0;
	}

	//タイマー4
	if (m_timer4 > 2.3f && m_timer4 < 2.5f)
	{
		m_upDown4 += 7.0f;
	}
	else if (m_timer4 > 2.6 && m_timer4 < 2.8f)
	{
		m_upDown4 -= 7.0f;
	}
	else if (m_timer4 > 2.8f)
	{
		m_timer4 = 0;
		m_upDown4 = 0;
	}

	//タイマー5
	if (m_timer5 > 2.9f && m_timer5 < 3.1f)
	{
		m_upDown5 += 7.0f;
	}
	else if (m_timer5 > 3.2 && m_timer5 < 3.4f)
	{
		m_upDown5 -= 7.0f;
	}
	else if (m_timer5 > 3.4f)
	{
		m_timer5 = 0;
		m_upDown5 = 0;
	}
}

void TitleUi::Timer()
{
	m_timer1 += g_gameTime->GetFrameDeltaTime();
	m_timer2 += g_gameTime->GetFrameDeltaTime();
	m_timer3 += g_gameTime->GetFrameDeltaTime();
	m_timer4 += g_gameTime->GetFrameDeltaTime();
	m_timer5 += g_gameTime->GetFrameDeltaTime();
}

void TitleUi::Render(RenderContext& rc)
{
	m_fire2.Draw(rc);
	m_water2.Draw(rc);
	m_wind2.Draw(rc);
	m_wind1.Draw(rc);
	m_heart3.Draw(rc);
	m_heart1.Draw(rc);
	m_shine2.Draw(rc);
	m_water1.Draw(rc);
	m_heart2.Draw(rc);
	m_shine1.Draw(rc);
	m_fire1.Draw(rc);
}