#include "stdafx.h"
#include "Loading.h"

Loading::Loading()
{

}

Loading::~Loading()
{

}

bool Loading::Start()
{
	m_render.Init("Assets/sprite/fade.dds", 1920, 1080);

	return true;
}

void Loading::Update()
{
	switch (m_state) 
	{
	case en_In:
		m_alpha -= 1.0f * g_gameTime->GetFrameDeltaTime();
		if (m_alpha <= 0.0f) 
		{
			m_alpha = 0.0f;
			m_state = en_Idle;
		}
		break;

	case en_Out:
		m_alpha += 1.0f * g_gameTime->GetFrameDeltaTime();
		if (m_alpha >= 1.0f) 
		{
			m_alpha = 1.0f;
			m_state = en_Idle;
		}
		break;

	case en_Idle:

		break;
	}
}

void Loading::Render(RenderContext& rc)
{
	if (m_alpha > 0.0f)
	{
		m_render.SetMulColor({ 1.0f, 1.0f, 1.0f, m_alpha });
		m_render.Draw(rc);
	}
}