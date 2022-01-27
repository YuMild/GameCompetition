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
	
	if (m_game->GetManageState() == 1)							//	�v���C���[�����S������
	{
		m_timeScoreOld = m_timeScore;							//	���S���̌o�ߎ��Ԃ��L�^
		m_puddingScoreOld = m_puddingScore;						//	���S���̊l���v���������L�^
		m_totalScoreOld = m_totalScore;							//	���S���̃g�[�^���X�R�A���L�^
	}
}
