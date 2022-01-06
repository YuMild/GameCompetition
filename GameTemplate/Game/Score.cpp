#include "stdafx.h"
#include "Score.h"

#include "Game.h"
#include "Pudding.h"

bool Score::Start()
{
	m_game = FindGO<Game>("game");

	return true;
}

void Score::Update()
{
	m_timeScoreTimer += g_gameTime->GetFrameDeltaTime();
	m_totalScoreTimer += g_gameTime->GetFrameDeltaTime();
	m_timeScore = m_timeScoreTimer * 100.0f;
	m_totalScore = m_totalScoreTimer * 100.0f;
	
	if (m_game->GetManageState() == 1)
	{
		m_timeScoreOld = m_timeScore;
		m_puddingScoreOld = m_puddingScore;
		m_totalScoreOld = m_totalScore;
	}
}
