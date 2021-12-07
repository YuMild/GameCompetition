#include "stdafx.h"
#include "Title.h"

#include "Game.h"
#include "Loading.h"
#include "TitleUi.h"

Title::Title()
{
}

Title::~Title() 
{
}

bool Title::Start()
{
	//‰æ‘œ
	m_titleRender.Init("Assets/sprite/Title.dds", 1920.0f, 1080.0f);

	//‰¹º
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/Title.wav");
	m_titleBGM = NewGO<SoundSource>(0);
	m_titleBGM->Init(0);
	m_titleBGM->Play(true);

	return true;
}

void Title::Update()
{
	/*if (m_isWaitFadeOut) {
		if (!m_loading->FadeNow())
		NewGO<Loading>(0, "loading");
		DeleteGO(this);
	}*/

	if (g_pad[0]->IsTrigger(enButtonStart))
	{
		NewGO<Game>(0, "game");
		
		DeleteGO(this);
		DeleteGO(m_titleBGM);
	}

	/*
	if (m_loading)
	{
		m_alpha += g_gameTime->GetFrameDeltaTime() * 20.0f;
	}
	else
	{
		m_alpha += g_gameTime->GetFrameDeltaTime() * 1.0f;
	}

	m_pressButton.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, fabsf(sinf(m_alpha))));*/

	m_titleRender.Update();
	//m_pressButton.Update();
}

void Title::Render(RenderContext& rc)
{
	m_titleRender.Draw(rc);
	//m_pressButton.Draw(rc);
}