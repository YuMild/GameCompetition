#include "stdafx.h"
#include "Title.h"
#include "Game.h"

Title::Title() {

}

Title::~Title() {

}

bool Title::Start() {
	//‰æ‘œ
	render.Init("Assets/sprite/title.dds", 1920.0f, 1080.0f);
	//‰¹º
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/title.wav");
	titleBGM = NewGO<SoundSource>(0);
	titleBGM->Init(0);
	titleBGM->Play(true);
	return true;
}

void Title::Update() {
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0, "game");
		DeleteGO(this);
		DeleteGO(titleBGM);
	}
}

void Title::Render(RenderContext& rc) {
	render.Draw(rc);
}