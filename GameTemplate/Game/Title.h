#pragma once

#include "sound/SoundSource.h"

class TitleUi;

class Title : public IGameObject
{
public:

	Title();
	~Title();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:

	//âÊëú
	SpriteRender m_render;
	//âπê∫
	SoundSource* m_titleBGM;

	TitleUi* m_titleUi;
};