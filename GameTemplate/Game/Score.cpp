#include "stdafx.h"
#include "Score.h"

#include "FontNumber.h"
#include "Game.h"
#include "Pudding.h"

bool Score::Start()
{
	m_game = FindGO<Game>("game");

	return true;
}

void Score::Update()
{
	m_timer += g_gameTime->GetFrameDeltaTime();
	m_score = m_timer * 100.0f;
	
	if (m_game->GetManageState() == 1)
	{
		m_scoreOld = m_score;
	}
}
