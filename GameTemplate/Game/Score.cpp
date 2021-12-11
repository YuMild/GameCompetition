#include "stdafx.h"
#include "Score.h"

bool Score::Start()
{
	m_score = 100;
	m_text += std::to_wstring(m_score);
	m_fontRender.SetText(m_text.c_str());
	m_fontRender.SetPosition(Vector3(-520.0f, 0.0f, 0.0f));

	return true;
}

void Score::Update()
{
	m_timer += g_gameTime->GetFrameDeltaTime();
	m_score = m_timer * 100.0f;
	m_text = std::to_wstring(m_score);
	m_fontRender.SetText(m_text.c_str());
}

void Score::Render(RenderContext& rc)
{
	m_fontRender.Draw(rc);
}