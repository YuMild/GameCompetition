#pragma once
#include "sound/SoundSource.h"

class FontNumber;

class GameOver : public IGameObject
{
public:

    GameOver();
    ~GameOver();
    bool Start();
    void Update();
    void Render(RenderContext& rc);

private:
    SpriteRender m_render;

    FontNumber* m_fontNumber;
};