#include "stdafx.h"
#include "Result.h"

#include "FontNumber.h"
#include "Game.h"
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
	m_resultBackGroundRender.Init("Assets/sprite/Result/ResultBackGround.DDS", 1700.0f, 900.0f);
	m_resultBackGroundRender.SetPosition({ 0.0,-30.0,0.0f });
	m_resultBackGroundRender.Update();
	m_resultRender.Init("Assets/sprite/Result/Result.DDS", 600.0f, 600.0f);
	m_resultRender.SetPosition({ 0.0f,420.0f,0.0f });
	m_resultRender.Update();

	m_score = FindGO<Score>("score");
	
	m_resultScore = m_score->GetScoreOld();

	m_fontNumber = NewGO<FontNumber>(0, "fontNumber");
	m_fontNumber->Init(m_resultScore);
	m_fontNumber->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	m_fontNumber->SetScale(Vector3(1.0f, 1.0f, 1.0f));

	m_game = FindGO<Game>("game");

	return true;
}

void Result::Update()
{
	m_stateTimer += g_gameTime->GetFrameDeltaTime();

	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Title>(0, "title");
		DeleteGO(this);
	}
	ManageState();
}

void Result::Render(RenderContext& rc)
{
	switch (m_resultState)
	{
	case 0://生存時
		break;

	case 1://スロー時
		break;

	case 2://フィニッシュ時
		
	case 3://リザルト表示
		m_resultBackGroundRender.Draw(rc);
		m_resultRender.Draw(rc);

		if (m_stateTimer > 1.0f)
		{
			m_resultState = 4;
			m_stateTimer = 0.0f;
		}
		break;

	case 4:
		break;
	}
}

void Result::ManageState()
{
	switch (m_game->GetManageState())
	{
	case0://生存時
		break;

	case1://スロー時
		m_resultState = 1;
		break;

	case2://フィニッシュ時
		m_resultState = 2;
		break;

	case 3://リザルト表示
		m_resultState = 3;
		break;
	}
}