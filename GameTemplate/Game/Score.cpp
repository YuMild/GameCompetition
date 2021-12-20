#include "stdafx.h"
#include "Score.h"

#include "FontNumber.h"
#include "Pudding.h"

bool Score::Start()
{
	return true;
}

void Score::Update()
{
	m_timer += g_gameTime->GetFrameDeltaTime();
	m_score = m_timer * 100.0f;
}
