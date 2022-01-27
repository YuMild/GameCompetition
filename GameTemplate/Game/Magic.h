#pragma once

class Game;
class Mp;
class Player;

/// <summary>
/// 魔法
/// </summary>
class Magic :public IGameObject
{
public:
	Magic();
	~Magic();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:

	/// <summary>
	/// MPバーの表示を管理
	/// </summary>
	void Cut();

	//	フレーム
	SpriteRender m_typeFrame[4];
	SpriteRender m_typeFrameGray[4];

	//	魔法
	SpriteRender m_typeFire;
	SpriteRender m_typeWater;
	SpriteRender m_typeWind;
	SpriteRender m_typeShine;

	//	魔法のグレー
	SpriteRender m_typeFireCoolTime;
	SpriteRender m_typeWaterCoolTime;
	SpriteRender m_typeWindCoolTime;
	SpriteRender m_typeShineCoolTime;

	//	鎖
	SpriteRender m_fireChain;
	SpriteRender m_waterChain;
	SpriteRender m_windChain;
	SpriteRender m_shineChain;

	Game* m_game;
	Mp* m_mp;
	Player* m_player;

	int m_num = 4;
};

