#include "stdafx.h"
#include "Title.h"

#include "Fade.h"
#include "Game.h"

namespace
{
	const float WIDTH = 1920.0f;	//幅
	const float HEIGHT = 1080.0f;	//高さ
}

Title::Title()
{
}

Title::~Title() 
{
	DeleteGO(m_titleBGM);
}

bool Title::Start()
{
	//背景
	m_titleRender.Init("Assets/sprite/Windows/Title.dds", WIDTH, 1080.0f);
	//PressStart
	m_pressStartRender.Init("Assets/sprite/Windows/PressStart.dds", 1000.0f, 1000.0f);
	//アイコン
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

	//音声
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/Title.wav");
	m_titleBGM = NewGO<SoundSource>(0);
	m_titleBGM->Init(0);
	m_titleBGM->Play(true);

	g_soundEngine->ResistWaveFileBank(16, "Assets/sound/Button.wav");

	m_fade = FindGO<Fade>("fade");
	m_fade->StartFadeIn();
	return true;
}

void Title::Update()
{
	State();
	Timer();

	if (m_isWaitFadeOut == true) {
		if (!m_fade->IsFade()) {
			NewGO<Game>(0, "game");
			//自身を削除する。
			DeleteGO(this);
		}
	}
	else {
		//Aボタンを押したら。
		if (g_pad[0]->IsTrigger(enButtonStart)) {
			m_isWaitFadeOut = true;
			m_fade->StartFadeOut();
			//効果音を再生する。
			m_buttonSE = NewGO<SoundSource>(16);
			m_buttonSE->Init(16);
			m_buttonSE->Play(false);
			m_buttonSE->SetVolume(0.5f);
		}
	}

	//a値を変化させる。
	if (m_isWaitFadeOut == true)
	{
		m_alpha += g_gameTime->GetFrameDeltaTime() * 20.5f;
	}
	else
	{
		m_alpha += g_gameTime->GetFrameDeltaTime() * 1.2f;
	}

	//スタートボタンの画像のアルファ値を変更する。
	m_pressStartRender.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, fabsf(sinf(m_alpha))));

	//背景
	m_titleRender.Update();

	//PressStart
	m_pressStartRender.Update();

	//アイコン
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

void Title::State()
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

void Title::Timer()
{
	m_timer1 += g_gameTime->GetFrameDeltaTime();
	m_timer2 += g_gameTime->GetFrameDeltaTime();
	m_timer3 += g_gameTime->GetFrameDeltaTime();
	m_timer4 += g_gameTime->GetFrameDeltaTime();
	m_timer5 += g_gameTime->GetFrameDeltaTime();
}

void Title::Render(RenderContext& rc)
{
	//背景
	m_titleRender.Draw(rc);

	//アイコン
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

	//PressStart
	m_pressStartRender.Draw(rc);
}