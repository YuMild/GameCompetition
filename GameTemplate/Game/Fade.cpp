#include "stdafx.h"
#include "Fade.h"

namespace
{
	const float SQUARE_WIDTH = 1000.0f;
	const float SQUARE_HEIGHT = 1000.0f;
}

Fade::Fade()
{
}


Fade::~Fade()
{
}

bool Fade::Start()
{
	m_spriteRender.Init("Assets/sprite/Windous/Fade.dds", SQUARE_WIDTH, SQUARE_HEIGHT);
	m_spriteRender.Update();
	return true;
}

void Fade::Update()
{
	switch (m_state) 
	{

	case enState_FadeIn:
		m_currentAlpha -= 1.0f * g_gameTime->GetFrameDeltaTime();
		if (m_currentAlpha <= 0.0f) {
			m_currentAlpha = 0.0f;
			m_state = enState_Idle;
		}
		break;

	case enState_FadeOut:
		m_currentAlpha += 1.0f * g_gameTime->GetFrameDeltaTime();
		if (m_currentAlpha >= 1.0f) {
			m_currentAlpha = 1.0f;
			m_state = enState_Idle;
		}
		break;

	case enState_Idle:
		break;
	}
}

void Fade::Render(RenderContext& rc)
{
	if (m_currentAlpha > 0.0f) {
		m_spriteRender.SetMulColor({ 1.0f, 1.0f, 1.0f, m_currentAlpha });
		m_spriteRender.Draw(rc);
	}
}