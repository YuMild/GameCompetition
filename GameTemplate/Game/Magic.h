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
	void Render(RenderContext& rc);

private:
	SpriteRender m_typeFire;
	SpriteRender m_typeWater;
	SpriteRender m_typeWind;
	SpriteRender m_typeShine;
	SpriteRender m_typeFireCoolTime;
	SpriteRender m_typeWaterCoolTime;
	SpriteRender m_typeWindCoolTime;
	SpriteRender m_typeShineCoolTime;

	Mp* m_mp;
	Player* m_player;
};

