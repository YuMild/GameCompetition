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

	//�摜
	SpriteRender m_render;
	//����
	SoundSource* m_titleBGM;

	TitleUi* m_titleUi;
};