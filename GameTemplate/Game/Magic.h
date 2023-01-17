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
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

private:

	/// <summary>
	/// MPバーの表示を管理
	/// </summary>
	void Cut();

	//	フレーム
	SpriteRender			m_typeFrame[4];
	SpriteRender			m_typeFrameGray[4];

	//	魔法
	SpriteRender			m_typeFire;
	SpriteRender			m_typeWater;
	SpriteRender			m_typeWind;
	SpriteRender			m_typeShine;

	//	魔法のグレー
	SpriteRender			m_typeFireCoolTime;
	SpriteRender			m_typeWaterCoolTime;
	SpriteRender			m_typeWindCoolTime;
	SpriteRender			m_typeShineCoolTime;

	//	鎖
	SpriteRender			m_fireChain;
	SpriteRender			m_waterChain;
	SpriteRender			m_windChain;
	SpriteRender			m_shineChain;

	Game*					m_game				= nullptr;
	Mp*						m_mp				= nullptr;
	Player*					m_player			= nullptr;

	int						m_num				= 4;
};

