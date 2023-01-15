#include "stdafx.h"
#include "Title.h"

#include "Fade.h"
#include "Game.h"

namespace
{
	const float BUTTON_SE_VOLUME = 0.5f;

	//	画像
	const float WIDTH = 1920.0f;
	const float HEIGHT = 1080.0f;
	const float SQUARE_WIDTH = 1000.0f;
	const float SQUARE_HEIGHT = 1000.0f;
	const float HEART_1_SIZE = 650.0f;
	const float HEART_2_SIZE = 460.0f;
	const float HEART_3_SIZE = 300.0f;
	const float FIRE_1_SIZE = 380.0f;
	const float FIRE_2_SIZE = 520.0f;
	const float WATER_1_SIZE = 330.0f;
	const float WATER_2_SIZE = 370.0f;
	const float WIND_1_SIZE = 550.0f;
	const float WIND_2_SIZE = 340.0f;
	const float SHINE_1_SIZE = 360.0f;
	const float SHINE_2_SIZE = 800.0f;

	//	ポジション
	const float HEART_1_X = 800.0f;
	const float HEART_1_Y = -440.0f;
	const float HEART_2_X = -670.0f;
	const float HEART_2_Y = -500.0f;
	const float HEART_3_X = 180.0f;
	const float HEART_3_Y = -570.0f;
	const float FIRE_1_X = 570.0f;
	const float FIRE_1_Y = -530.0f;
	const float FIRE_2_X = -460.0f;
	const float FIRE_2_Y = -470.0f;
	const float WATER_1_X = -420.0f;
	const float WATER_1_Y = -560.0f;
	const float WATER_2_X = 180.0f;
	const float WATER_2_Y = -490.0f;
	const float WIND_1_X = 450.0f;
	const float WIND_1_Y = -520.0f;
	const float WIND_2_X = -250.0f;
	const float WIND_2_Y = -510.0f;
	const float SHINE_1_X = -40.0f;
	const float SHINE_1_Y = -520.0f;
	const float SHINE_2_X = -850.0f;
	const float SHINE_2_Y = -450.0f;
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
	//	背景
	m_titleRender.Init("Assets/sprite/Windows/Title.dds", WIDTH, HEIGHT);

	//	PressStart
	m_pressStartRender.Init("Assets/sprite/Windows/PressStart.dds", SQUARE_WIDTH, SQUARE_HEIGHT);

	//	アイコン
	m_heart1.Init("Assets/sprite/Hp/HP1.DDS", HEART_1_SIZE, HEART_1_SIZE);
	m_heart2.Init("Assets/sprite/Hp/HP2.DDS", HEART_2_SIZE, HEART_2_SIZE);
	m_heart3.Init("Assets/sprite/Hp/HP3.DDS", HEART_3_SIZE, HEART_3_SIZE);
	m_fire1.Init("Assets/sprite/Magic/TypeFire.DDS", FIRE_1_SIZE, FIRE_1_SIZE);
	m_fire2.Init("Assets/sprite/Magic/TypeFire.DDS", FIRE_2_SIZE, FIRE_2_SIZE);
	m_water1.Init("Assets/sprite/Magic/TypeWater.DDS", WATER_1_SIZE, WATER_1_SIZE);
	m_water2.Init("Assets/sprite/Magic/TypeWater.DDS", WATER_2_SIZE, WATER_2_SIZE);
	m_wind1.Init("Assets/sprite/Magic/TypeWind.DDS", WIND_1_SIZE, WIND_1_SIZE);
	m_wind2.Init("Assets/sprite/Magic/TypeWind.DDS", WIND_2_SIZE, WIND_2_SIZE);
	m_shine1.Init("Assets/sprite/Magic/TypeShine.DDS", SHINE_1_SIZE, SHINE_1_SIZE);
	m_shine2.Init("Assets/sprite/Magic/TypeShine.DDS", SHINE_2_SIZE, SHINE_2_SIZE);

	//	音声
	g_soundEngine->ResistWaveFileBank(enInitSoundNumber_Title, "Assets/sound/Title.wav");
	m_titleBGM = NewGO<SoundSource>(0);
	m_titleBGM->Init(enInitSoundNumber_Title);
	m_titleBGM->Play(true);

	g_soundEngine->ResistWaveFileBank(enInitSoundNumber_Button, "Assets/sound/Button.wav");

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
			//	自身を削除する。
			DeleteGO(this);
		}
	}

	else {
		//	Aボタンを押したら。
		if (g_pad[0]->IsTrigger(enButtonStart)) {
			m_isWaitFadeOut = true;
			m_fade->StartFadeOut();
			//	効果音を再生する。
			m_buttonSE = NewGO<SoundSource>(0);
			m_buttonSE->Init(enInitSoundNumber_Button);
			m_buttonSE->Play(false);
			m_buttonSE->SetVolume(BUTTON_SE_VOLUME);
		}
	}

	//	a値を変化させる。
	if (m_isWaitFadeOut == true)
	{
		m_alpha += g_gameTime->GetFrameDeltaTime() * 20.5f;
	}
	else
	{
		m_alpha += g_gameTime->GetFrameDeltaTime() * 1.2f;
	}

	//	スタートボタンの画像のアルファ値を変更する。
	m_pressStartRender.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, fabsf(sinf(m_alpha))));

	//	背景
	m_titleRender.Update();

	//	PressStart
	m_pressStartRender.Update();

	//	アイコン
	m_heart1Position = { HEART_1_X,HEART_1_Y + m_upDown1,0.0f };
	m_heart1.SetPosition(m_heart1Position);
	m_heart1.Update();
	m_wind2Position = { WIND_2_X,WIND_2_Y + m_upDown1,0.0f };
	m_wind2.SetPosition(m_wind2Position);
	m_wind2.Update();

	m_shine2Position = { SHINE_2_X,SHINE_2_Y + m_upDown2,0.0f };
	m_shine2.SetPosition(m_shine2Position);
	m_shine2.Update();
	m_heart3Position = { HEART_3_X,HEART_3_Y + m_upDown2,0.0f };
	m_heart3.SetPosition(m_heart3Position);
	m_heart3.Update();

	m_water1Position = { WATER_1_X,WATER_1_Y + m_upDown3,0.0f };
	m_water1.SetPosition(m_water1Position);
	m_water1.Update();
	m_water2Position = { WATER_2_X,WATER_2_Y + m_upDown3,0.0f };
	m_water2.SetPosition(m_water2Position);
	m_water2.Update();

	m_fire2Position = { FIRE_2_X,FIRE_2_Y + m_upDown4,0.0f };
	m_fire2.SetPosition(m_fire2Position);
	m_fire2.Update();
	m_wind1Position = { WIND_1_X,WIND_1_Y + m_upDown4,0.0f };
	m_wind1.SetPosition(m_wind1Position);
	m_wind1.Update();

	m_heart2Position = { HEART_2_X,HEART_2_Y + m_upDown5,0.0f };
	m_heart2.SetPosition(m_heart2Position);
	m_heart2.Update();
	m_shine1Position = { SHINE_1_X,SHINE_1_Y + m_upDown5,0.0f };
	m_shine1.SetPosition(m_shine1Position);
	m_shine1.Update();
	m_fire1Position = { FIRE_1_X,FIRE_1_Y + m_upDown5,0.0f };
	m_fire1.SetPosition(m_fire1Position);
	m_fire1.Update();
}

void Title::State()
{
	//	タイマー1
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

	//	タイマー2
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

	//	タイマー3
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

	//	タイマー4
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

	//	タイマー5
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
	//	背景
	m_titleRender.Draw(rc);

	//	アイコン
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

	//	PressStart
	m_pressStartRender.Draw(rc);
}