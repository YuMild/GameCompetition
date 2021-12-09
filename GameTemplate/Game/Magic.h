#pragma once

class Mp;
class Player;

class Magic :public IGameObject
{
public:
	Magic();
	~Magic();
	bool Start();
	void Update();
	void Cut();
	void Render(RenderContext& rc);

private:
	SpriteRender m_typeFrame[4];
	SpriteRender m_typeFire;
	SpriteRender m_typeWater;
	SpriteRender m_typeWind;
	SpriteRender m_typeShine;
	SpriteRender m_typeFireCoolTime;
	SpriteRender m_typeWaterCoolTime;
	SpriteRender m_typeWindCoolTime;
	SpriteRender m_typeShineCoolTime;
	SpriteRender m_fireChain;
	SpriteRender m_waterChain;
	SpriteRender m_windChain;
	SpriteRender m_shineChain;

	Mp* m_mp;
	Player* m_player;

	int m_num = 4;
};

