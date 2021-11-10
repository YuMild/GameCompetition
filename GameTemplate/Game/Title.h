#pragma once
class Title
{
};

#pragma once

#include "sound/SoundSource.h"

class Title : public IGameObject
{
public:
	Title();
	~Title();
	void Update();
	void Render(RenderContext& rc);

	SpriteRender titleRender;
	SpriteRender cursorRender;
	SpriteRender gamestartRender;
	SpriteRender helpRender;

	Vector3 cursorposition;
	Vector3 gamestartposition;
	Vector3 helpposition;

	int titleState;

	SoundSource* titleBGM;
	SoundSource* pikoSE;
};