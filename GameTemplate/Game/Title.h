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

	//‰æ‘œ
	SpriteRender m_render;
	//‰¹º
	SoundSource* m_titleBGM;
};