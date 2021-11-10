#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"
#include "sound/SoundEngine.h"

GameOver::GameOver() {
    //ゲームクリアの画像を読み込む。
    spriteRender.Init("Assets/sprite/gameover.dds", 1280.0f, 720.0f);
}

GameOver::~GameOver()
{

}

void GameOver::Update()
{
    if (g_pad[0]->IsTrigger(enButtonA))
    {
        NewGO<Title>(0, "title");
        DeleteGO(this);
    }
}

void GameOver::Render(RenderContext& rc) {
    spriteRender.Draw(rc);
}