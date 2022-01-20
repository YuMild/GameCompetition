#include "stdafx.h"
#include "Result.h"

#include "FontBlueNumber.h"
#include "FontPurpleNumber.h"
#include "Game.h"
#include "Pudding.h"
#include "Score.h"
#include "Title.h"
#include "sound/SoundEngine.h"

Result::Result()
{

}

Result::~Result()
{

}

bool Result::Start()
{
	//リザルト
	m_resultBackGroundRender.Init("Assets/sprite/Result/Result/ResultBackGround.DDS", 1700.0f, 900.0f);
	m_resultBackGroundRender.SetPosition({ 0.0,-30.0,0.0f });
	m_resultBackGroundRender.Update();
	m_resultRender.Init("Assets/sprite/Result/Result/Result.DDS", 600.0f, 600.0f);
	m_resultRender.SetPosition({ 0.0f,420.0f,0.0f });
	m_resultRender.Update();
	m_timeRender.Init("Assets/sprite/Result/Result/Time.DDS", 300.0f, 300.0f);
	m_timeRender.SetPosition({ -600.0f,200.0f,0.0f });
	m_timeRender.Update();
	m_puddingRender.Init("Assets/sprite/Result/Result/Pudding.DDS", 500.0f, 500.0f);
	m_puddingRender.SetPosition({ -495.0f,20.0f,0.0f });
	m_puddingRender.Update();
	m_totalScoreRender.Init("Assets/sprite/Result/Result/totalScore.DDS", 700.0f, 700.0f);
	m_totalScoreRender.SetPosition({ -400.0f,-280.0f,0.0f });
	m_totalScoreRender.Update();

	//ランク
	m_sRender.Init("Assets/sprite/Result/Rank/S.DDS", 1000.0f, 1000.0f);
	m_sRender.SetPosition({ 0.0f,50.0f,0.0f });
	m_sRender.Update();
	m_aRender.Init("Assets/sprite/Result/Rank/A.DDS", 1000.0f, 1000.0f);
	m_aRender.SetPosition({ 0.0f,50.0f,0.0f });
	m_aRender.Update();
	m_bRender.Init("Assets/sprite/Result/Rank/B.DDS", 1000.0f, 1000.0f);
	m_bRender.SetPosition({ 0.0f,50.0f,0.0f });
	m_bRender.Update();
	m_cRender.Init("Assets/sprite/Result/Rank/C.DDS", 1000.0f, 1000.0f);
	m_cRender.SetPosition({ 0.0f,50.0f,0.0f });
	m_cRender.Update();
	m_dRender.Init("Assets/sprite/Result/Rank/D.DDS", 1000.0f, 1000.0f);
	m_dRender.SetPosition({ 0.0f,50.0f,0.0f });
	m_dRender.Update();

	//サウンド
	g_soundEngine->ResistWaveFileBank(14, "Assets/sound/DrumRoll2.wav");
	m_drumRollSE = NewGO<SoundSource>(14);
	m_drumRollSE->Init(14);
	m_drumRollSE->Play(false);

	g_soundEngine->ResistWaveFileBank(15, "Assets/sound/Drum.wav");

	m_game = FindGO<Game>("game");
	m_pudding = FindGO<Pudding>("pudding");
	m_score = FindGO<Score>("score");

	m_timeScore = m_score->GetTimeScoreOld();
	m_puddingScore = m_score->GetPuddingScoreOld();
	m_totalScore = m_score->GetTotalScoreOld();

	return true;
}

void Result::Update()
{
	if (m_resultState >=7 && g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Title>(0, "title");
		DeleteGO(m_fontPurpleNumber);
		DeleteGO(m_game);
		DeleteGO(this);
	}
	ManageState();
}

void Result::Render(RenderContext& rc)
{
	if (m_resultState >= 3)//リザルト表示
	{
		m_resultBackGroundRender.Draw(rc);
		m_resultRender.Draw(rc);
		m_totalScoreRender.Draw(rc);

		if (m_resultState <= 6)
		{
			m_timeRender.Draw(rc);
			m_puddingRender.Draw(rc);
		}
	}

	//タイムスコア表示
	if (m_resultState >= 4 && m_isStart4 == true)
	{
		m_timeNumber = NewGO<FontBlueNumber>(0, "fontBlueNumber");
		m_timeNumber->Init(m_timeScore);
		m_timeNumber->SetPosition(Vector3(650.0f, 200.0f, 0.0f));
		m_timeNumber->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		m_drumSE = NewGO<SoundSource>(15);
		m_drumSE->Init(15);
		m_drumSE->Play(false);

		m_isStart4 = false;
	}

	//プリンスコア表示
	if (m_resultState >= 5 && m_isStart5 == true)
	{
		m_puddingNumber = NewGO<FontBlueNumber>(0, "fontBlueNumber");
		m_puddingNumber->Init(m_puddingScore);
		m_puddingNumber->SetPosition(Vector3(650.0f, 20.0f, 0.0f));
		m_puddingNumber->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		m_drumSE = NewGO<SoundSource>(15);
		m_drumSE->Init(15);
		m_drumSE->Play(false);

		m_isStart5 = false;
	}

	//トータルスコア表示
	if (m_resultState >= 6 && m_isStart6 == true)
	{
		m_fontPurpleNumber = NewGO<FontPurpleNumber>(0, "fontPurpleNumber");
		m_fontPurpleNumber->Init(m_totalScore);
		m_fontPurpleNumber->SetPosition(Vector3(650.0f, -280.0f, 0.0f));
		m_fontPurpleNumber->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		m_drumSE = NewGO<SoundSource>(15);
		m_drumSE->Init(15);
		m_drumSE->Play(false);

		m_isStart6 = false;
	}

	//ランク表示
	if (m_resultState == 7)
	{
		m_dRender.Draw(rc);
		m_dRender.SetScale({ 1.0,1.0,0.0f });
		m_dRender.Update();
		DeleteGO(m_timeNumber);
		DeleteGO(m_puddingNumber);
	}

	if (m_resultState == 8)
	{
		m_cRender.Draw(rc);
		DeleteGO(m_timeNumber);
		DeleteGO(m_puddingNumber);
	}

	if (m_resultState == 9)
	{
		m_bRender.Draw(rc);
		DeleteGO(m_timeNumber);
		DeleteGO(m_puddingNumber);
	}

	if (m_resultState == 10)
	{
		m_aRender.Draw(rc);
		DeleteGO(m_timeNumber);
		DeleteGO(m_puddingNumber);
	}

	if (m_resultState == 11)
	{
		m_sRender.Draw(rc);
		DeleteGO(m_timeNumber);
		DeleteGO(m_puddingNumber);
	}
}

void Result::ManageState()
{
	switch (m_game->GetManageState())
	{
	case 1:
		m_resultState = 1;
		break;
	case 2:
		m_resultState = 2;
		break;
	case 3:
		m_resultState = 3;
		break;
	case 4:
		m_resultState = 4;
		break;
	case 5:
		m_resultState = 5;
		break;
	case 6:
		m_resultState = 6;
		break;
	case 7:
		m_resultState = 7;
		break;
	case 8:
		m_resultState = 8;
		break;
	case 9:
		m_resultState = 9;
		break;
	case 10:
		m_resultState = 10;
		break;
	case 11:
		m_resultState = 11;
		break;
	}
}