#include "stdafx.h"
#include "Title.h"

Title::Title() {

}

Title::~Title() {

}

bool Title::Start() {
	//‰æ‘œ
	title.Init("Assets/sprite/title.dds", 1280.0f, 720.0f);
	cursor.Init("Assets/sprite/cursor.dds", 50.0f, 50.0f);
	start.Init("Assets/sprite/gamestart.dds", 300.0f, 300.0f);
	help.Init("Assets/sprite/help.dds", 300.0f, 300.0f);

	//ƒ|ƒWƒVƒ‡ƒ“
	cursorPosition.x = -135.0f;
	cursorPosition.y = -30.0f;
	startPosition.x = 60.0f;
	startPosition.y = -35.0f;
	helpPosition.x = -35.0f;
	helpPosition.y = -100.0f;
}

void Title::Update() {
	switch (titleState) {
	case 0:
		if (g_pad[0]->IsTrigger(enButtonUp) || g_pad[0]->IsTrigger(enButtonDown))
		{
			titleState = 1;
			pikoSE = NewGO<SoundSource>(1);
			pikoSE->Init(1);
			pikoSE->Play(false);
			cursorPosition.y = -95.0f;
			startPosition.x = 30.0f;
			helpPosition.x = -5.0f;
		}
		break;
	case 1:
		if (g_pad[0]->IsTrigger(enButtonUp) || g_pad[0]->IsTrigger(enButtonDown))
		{
			titleState = 0;
			pikoSE = NewGO<SoundSource>(1);
			pikoSE->Init(1);
			pikoSE->Play(false);
			cursorPosition.y = -30.0f;
			startPosition.x = 60.0f;
			helpPosition.x = -35.0f;
		}
		break;
	}
}

void Title::Render(RenderContext& rc) {

}