#pragma once

#include "sound/SoundSource.h"

class Title : public IGameObject
{
public:
	Title();
	~Title();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	//�摜
	SpriteRender title;
	//����
	SoundSource* titleBGM;
};