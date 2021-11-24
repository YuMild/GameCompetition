#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title() {

}

Title::~Title() {

}

bool Title::Start() {
	//‰æ‘œ
	m_render.Init("Assets/sprite/Title.dds", 1920.0f, 1080.0f);
	//‰¹º
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/Title.wav");
	m_titleBGM = NewGO<SoundSource>(0);
	m_titleBGM->Init(0);
	m_titleBGM->Play(true);
	return true;
}

void Title::Update() {
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0, "game");
		DeleteGO(this);
		DeleteGO(m_titleBGM);
	}
}

void Title::Render(RenderContext& rc) {
	m_render.Draw(rc);
}