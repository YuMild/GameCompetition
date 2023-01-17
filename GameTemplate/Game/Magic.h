#pragma once

class Game;
class Mp;
class Player;

/// <summary>
/// ���@
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
	/// MP�o�[�̕\�����Ǘ�
	/// </summary>
	void Cut();

	//	�t���[��
	SpriteRender			m_typeFrame[4];
	SpriteRender			m_typeFrameGray[4];

	//	���@
	SpriteRender			m_typeFire;
	SpriteRender			m_typeWater;
	SpriteRender			m_typeWind;
	SpriteRender			m_typeShine;

	//	���@�̃O���[
	SpriteRender			m_typeFireCoolTime;
	SpriteRender			m_typeWaterCoolTime;
	SpriteRender			m_typeWindCoolTime;
	SpriteRender			m_typeShineCoolTime;

	//	��
	SpriteRender			m_fireChain;
	SpriteRender			m_waterChain;
	SpriteRender			m_windChain;
	SpriteRender			m_shineChain;

	Game*					m_game				= nullptr;
	Mp*						m_mp				= nullptr;
	Player*					m_player			= nullptr;

	int						m_num				= 4;
};

