#include "stdafx.h"
#include "GameOver.h"
#include "Title.h"
#include "sound/SoundEngine.h"

GameOver::GameOver() {
   m_render.Init("Assets/sprite/GameOver.dds", 1920.0f, 1080.0f);
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
   m_render.Draw(rc);
}