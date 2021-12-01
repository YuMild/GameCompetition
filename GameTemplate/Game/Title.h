#pragma once

#include "sound/SoundSource.h"

class Loading;
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
	SpriteRender m_titleRender;
	SpriteRender m_pressButton;
	//âπê∫
	SoundSource* m_titleBGM;

	Loading* m_loading;
	TitleUi* m_titleUi;

	bool m_isWaitFadeOut = false;
	float m_alpha = 0.0f;
};