#pragma once

class Map;
class Mp;
class Player;
class MagicPoint :public IGameObject
{
public:

	void SetPosition(Vector3& position) {
		m_position = position;
	}
	MagicPoint();
	~MagicPoint();
	bool Start();
	void Update();
	void MapMove();

	void MagicPointMap(RenderContext& rc)
	{
		if (m_isStart == false)
		{
			return;
		}
		m_magicPointMap.Draw(rc);
	}
	void MagicPointMapGray(RenderContext& rc)
	{
		if (m_isStart == false)
		{
			return;
		}
		m_magicPointMapGray.Draw(rc);
	}

private:

	//画像
	SpriteRender m_magicPointMap;
	SpriteRender m_magicPointMapGray;

	//ベクトル
	Vector3 m_position;
	Vector3 m_diff;

	//エフェクト
	EffectEmitter* m_magicPointEF;
	EffectEmitter* m_magicPointDeleteEF;

	//サウンド
	SoundSource* m_magicPointSE;

	//参照
	Map* m_map;
	Mp* m_mp;
	Player* m_player;

	float m_aliveTimer = 0;
};

