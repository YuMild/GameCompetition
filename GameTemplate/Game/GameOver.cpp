#include "stdafx.h"
#include "GameOver.h"

#include "FontNumber.h"
#include "Title.h"
#include "sound/SoundEngine.h"

GameOver::GameOver()
{
  
}

GameOver::~GameOver()
{

}

bool GameOver::Start()
{
    m_fontNumber = NewGO<FontNumber>(0, "fontNumber");
    m_render.Init("Assets/sprite/GameOver.dds", 1920.0f, 1080.0f);
    return true;
}

void GameOver::Update()
{
    if (g_pad[0]->IsTrigger(enButtonA))
    {
        NewGO<Title>(0, "title");
        DeleteGO(this);
    }
}

void GameOver::Render(RenderContext& rc) 
{
   m_render.Draw(rc);
}