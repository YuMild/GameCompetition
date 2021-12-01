#include "stdafx.h"
#include "Title.h"

#include "Game.h"
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
	m_render.Init("Assets/sprite/Title.dds", 1920.0f, 1080.0f);

	//‰¹º
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/Title.wav");
	m_titleBGM = NewGO<SoundSource>(0);
	m_titleBGM->Init(0);
	m_titleBGM->Play(true);

	//m_titleUi = NewGO<TitleUi>(0,"titleUi");
	//m_titleUi->SetPosition(Vector3{ 300.0f,-300.0f,0.0f });
	//m_titleUi->SetScale(0.1f);

	return true;
}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonStart))
	{
		NewGO<Game>(0, "game");
		
		DeleteGO(this);
		DeleteGO(m_titleBGM);
	}
}

void Title::Render(RenderContext& rc)
{
	m_render.Draw(rc);
}