#pragma once
#include "sound/SoundSource.h"

class GameOver : public IGameObject
{
public:
    GameOver();
    ~GameOver();
    void Update();
    void Render(RenderContext& rc);
    SpriteRender m_render; //�摜�̕\��
};