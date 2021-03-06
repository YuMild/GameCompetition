#include "stdafx.h"
#include "Result.h"

#include "FontBlueNumber.h"
#include "FontPurpleNumber.h"
#include "Game.h"
#include "Pudding.h"
#include "Score.h"
#include "Title.h"
#include "sound/SoundEngine.h"

namespace
{
	//	画像の幅と高さ
	const float SQUARE_WIDTH = 1000.0f;
	const float SQUARE_HEIGHT = 1000.0f;
	const float RESULT_BACKGROUND_WIDTH = 1700.0f;
	const float RESULT_BACKGROUND_HEIGHT = 900.0f;
	const float RESULT_WIDTH = 600.0f;
	const float RESULT_HEIGHT = 600.0f;
	const float TIME_WIDTH = 300.0f;
	const float TIME_HRIGHT = 300.0f;
	const float PUDDING_WIDTH = 500.0f;
	const float PUDDING_HEIGHT = 500.0f;
	const float TOTALSCORE_WIDTH = 700.0f;
	const float TOTALSCORE_HEIGHT = 700.0f;

	//	ポジション
	const float RESULT_BACKGROUND_X = 0.0f;
	const float RESULT_BACKGROUND_Y = -30.0f;
	const float RESULT_X = 0.0f;
	const float RESULT_Y = 420.0f;
	const float TIME_X = -600.0F;
	const float TIME_Y = 200.0F;
	const float TIMESCORE_X = 650.0f;
	const float TIMESCORE_Y = 200.0f;
	const float PUDDING_X = -495.0f;
	const float PUDDING_Y = 20.0f;
	const float PUDDINGSCORE_X = 650.0f;
	const float PUDDINGSCORE_Y = 20.0f;
	const float TOTALSCORE_X = -400.0f;
	const float TOTALSCORE_Y = -280.0f;
	const float TOTALSCORE_FONT_X = 650.0f;
	const float TOTALSCORE_FONT_Y = -280.0f;
	const float RANK_X = 0.0f;
	const float RANK_Y = 50.0f;
}

Result::Result()
{

}

Result::~Result()
{

}

bool Result::Start()
{
	//	リザルト
	m_resultBackGroundRender.Init("Assets/sprite/Result/Result/ResultBackGround.DDS", RESULT_BACKGROUND_WIDTH, RESULT_BACKGROUND_HEIGHT);
	m_resultBackGroundRender.SetPosition({ RESULT_BACKGROUND_X,RESULT_BACKGROUND_Y,0.0f });
	m_resultBackGroundRender.Update();
	m_resultRender.Init("Assets/sprite/Result/Result/Result.DDS", RESULT_WIDTH, RESULT_HEIGHT);
	m_resultRender.SetPosition({ RESULT_X,RESULT_Y,0.0f });
	m_resultRender.Update();
	m_timeRender.Init("Assets/sprite/Result/Result/Time.DDS", TIME_WIDTH, TIME_HRIGHT);
	m_timeRender.SetPosition({ TIME_X,TIME_Y,0.0f });
	m_timeRender.Update();
	m_puddingRender.Init("Assets/sprite/Result/Result/Pudding.DDS", PUDDING_WIDTH, PUDDING_HEIGHT);
	m_puddingRender.SetPosition({ PUDDING_X,PUDDING_Y,0.0f });
	m_puddingRender.Update();
	m_totalScoreRender.Init("Assets/sprite/Result/Result/totalScore.DDS", TOTALSCORE_WIDTH, TOTALSCORE_HEIGHT);
	m_totalScoreRender.SetPosition({ TOTALSCORE_X,TOTALSCORE_Y,0.0f });
	m_totalScoreRender.Update();

	//	ランク
	m_sRender.Init("Assets/sprite/Result/Rank/S.DDS", SQUARE_WIDTH, SQUARE_HEIGHT);
	m_sRender.SetPosition({ RANK_X,RANK_Y,0.0f });
	m_sRender.Update();
	m_aRender.Init("Assets/sprite/Result/Rank/A.DDS", SQUARE_WIDTH, SQUARE_HEIGHT);
	m_aRender.SetPosition({ RANK_X,RANK_Y,0.0f });
	m_aRender.Update();
	m_bRender.Init("Assets/sprite/Result/Rank/B.DDS", SQUARE_WIDTH, SQUARE_HEIGHT);
	m_bRender.SetPosition({ RANK_X,RANK_Y,0.0f });
	m_bRender.Update();
	m_cRender.Init("Assets/sprite/Result/Rank/C.DDS", SQUARE_WIDTH, SQUARE_HEIGHT);
	m_cRender.SetPosition({ RANK_X,RANK_Y,0.0f });
	m_cRender.Update();
	m_dRender.Init("Assets/sprite/Result/Rank/D.DDS", SQUARE_WIDTH, SQUARE_HEIGHT);
	m_dRender.SetPosition({ RANK_X,RANK_Y,0.0f });
	m_dRender.Update();

	//	サウンド
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
		DeleteGO(m_totalScoreFont);
		DeleteGO(m_game);
		DeleteGO(this);
	}
	ManageState();
}

void Result::Render(RenderContext& rc)
{
	//	リザルト表示
	if (m_resultState >= 3)
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

	//	タイムスコア表示
	if (m_resultState >= 4 && m_isStart4 == true)
	{
		m_timeScoreFont = NewGO<FontBlueNumber>(0, "fontBlueNumber");
		m_timeScoreFont->Init(m_timeScore);
		m_timeScoreFont->SetPosition(Vector3(TIMESCORE_X, TIMESCORE_Y, 0.0f));
		m_timeScoreFont->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		m_drumSE = NewGO<SoundSource>(15);
		m_drumSE->Init(15);
		m_drumSE->Play(false);

		m_isStart4 = false;
	}

	//	プリンスコア表示
	if (m_resultState >= 5 && m_isStart5 == true)
	{
		m_puddingScoreFont = NewGO<FontBlueNumber>(0, "fontBlueNumber");
		m_puddingScoreFont->Init(m_puddingScore);
		m_puddingScoreFont->SetPosition(Vector3(PUDDINGSCORE_X, PUDDINGSCORE_Y, 0.0f));
		m_puddingScoreFont->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		m_drumSE = NewGO<SoundSource>(15);
		m_drumSE->Init(15);
		m_drumSE->Play(false);

		m_isStart5 = false;
	}

	//	トータルスコア表示
	if (m_resultState >= 6 && m_isStart6 == true)
	{
		m_totalScoreFont = NewGO<FontPurpleNumber>(0, "fontPurpleNumber");
		m_totalScoreFont->Init(m_totalScore);
		m_totalScoreFont->SetPosition(Vector3(TOTALSCORE_FONT_X, TOTALSCORE_FONT_Y, 0.0f));
		m_totalScoreFont->SetScale(Vector3(1.0f, 1.0f, 1.0f));

		m_drumSE = NewGO<SoundSource>(15);
		m_drumSE->Init(15);
		m_drumSE->Play(false);

		m_isStart6 = false;
	}

	//	ランク表示
	if (m_resultState == 7)
	{
		m_dRender.Draw(rc);
		DeleteGO(m_timeScoreFont);
		DeleteGO(m_puddingScoreFont);
	}

	if (m_resultState == 8)
	{
		m_cRender.Draw(rc);
		DeleteGO(m_timeScoreFont);
		DeleteGO(m_puddingScoreFont);
	}

	if (m_resultState == 9)
	{
		m_bRender.Draw(rc);
		DeleteGO(m_timeScoreFont);
		DeleteGO(m_puddingScoreFont);
	}

	if (m_resultState == 10)
	{
		m_aRender.Draw(rc);
		DeleteGO(m_timeScoreFont);
		DeleteGO(m_puddingScoreFont);
	}

	if (m_resultState == 11)
	{
		m_sRender.Draw(rc);
		DeleteGO(m_timeScoreFont);
		DeleteGO(m_puddingScoreFont);
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