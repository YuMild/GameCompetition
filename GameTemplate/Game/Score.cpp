#include "stdafx.h"
#include "Score.h"

#include "Game.h"
#include "Pudding.h"

namespace
{
	const int INT_TO_FLOAT = 100.0f;
}

bool Score::Start()
{
	m_game = FindGO<Game>("game");

	return true;
}

void Score::Update()
{
	m_timeScoreTimer += g_gameTime->GetFrameDeltaTime();
	m_totalScoreTimer += g_gameTime->GetFrameDeltaTime();

	m_timeScore = m_timeScoreTimer * INT_TO_FLOAT;
	m_totalScore = m_totalScoreTimer * INT_TO_FLOAT;
	
	if (m_game->GetManageState() == 1)							//	プレイヤーが死亡した時
	{
		m_timeScoreOld = m_timeScore;							//	死亡時の経過時間を記録
		m_puddingScoreOld = m_puddingScore;						//	死亡時の獲得プリン数を記録
		m_totalScoreOld = m_totalScore;							//	死亡時のトータルスコアを記録
	}
}
