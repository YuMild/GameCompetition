#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "sound/SoundEngine.h"

Title::Title()
{
	int titleState = 0;

	//‰æ‘œ
	titleRender.Init("Assets/sprite/title.dds", 1280.0f, 720.0f);
	cursorRender.Init("Assets/sprite/cursor.dds", 50.0f, 50.0f);
	gamestartRender.Init("Assets/sprite/gamestart.dds", 300.0f, 300.0f);
	helpRender.Init("Assets/sprite/help.dds", 300.0f, 300.0f);

	//ƒ|ƒWƒVƒ‡ƒ“
	cursorposition.x = -135.0f;
	cursorposition.y = -30.0f;
	gamestartposition.x = 60.0f;
	gamestartposition.y = -35.0f;
	helpposition.x = -35.0f;
	helpposition.y = -100.0f;

	//‰¹º
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/title.wav");
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/piko.wav");

	titleBGM = NewGO<SoundSource>(0);
	titleBGM->Init(0);
	titleBGM->Play(true);
}

Title::~Title()
{

}

void Title::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0, "game");
		DeleteGO(this);
		DeleteGO(titleBGM);
	}

	switch (titleState) {
	case 0:
		if (g_pad[0]->IsTrigger(enButtonUp) || g_pad[0]->IsTrigger(enButtonDown))
		{
			titleState = 1;
			pikoSE = NewGO<SoundSource>(1);
			pikoSE->Init(1);
			pikoSE->Play(false);
			cursorposition.y = -95.0f;
			gamestartposition.x = 30.0f;
			helpposition.x = -5.0f;
		}
		break;
	case 1:
		if (g_pad[0]->IsTrigger(enButtonUp) || g_pad[0]->IsTrigger(enButtonDown))
		{
			titleState = 0;
			pikoSE = NewGO<SoundSource>(1);
			pikoSE->Init(1);
			pikoSE->Play(false);
			cursorposition.y = -30.0f;
			gamestartposition.x = 60.0f;
			helpposition.x = -35.0f;
		}
		break;
	}

	cursorRender.Update();
	gamestartRender.Update();
	helpRender.Update();
	cursorRender.SetPosition(cursorposition);
	gamestartRender.SetPosition(gamestartposition);
	helpRender.SetPosition(helpposition);
}

void Title::Render(RenderContext& rc)
{
	titleRender.Draw(rc);
	cursorRender.Draw(rc);
	gamestartRender.Draw(rc);
	helpRender.Draw(rc);
}