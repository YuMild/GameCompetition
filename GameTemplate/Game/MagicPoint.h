#pragma once

class Map;
class Mp;
class Player;

/// <summary>
///	マジックポイント回復ポイント
/// </summary>
class MagicPoint :public IGameObject
{
public:

	/// <summary>
	///	座標を指定する
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(Vector3& position) {
		m_position = position;
	}

	/// <summary>
	/// マップ上に画像を生成する
	/// </summary>
	/// <param name="rc"></param>
	void MagicPointMap(RenderContext& rc)
	{
		if (m_isStart == false)
		{
			return;
		}
		m_magicPointMap.Draw(rc);
	}

	/// <summary>
	/// マップ上にグレー画像を生成する
	/// </summary>
	/// <param name="rc"></param>
	void MagicPointMapGray(RenderContext& rc)
	{
		if (m_isStart == false)
		{
			return;
		}
		m_magicPointMapGray.Draw(rc);
	}

	MagicPoint();
	~MagicPoint();
	bool Start();
	void Update();
	void MapMove();

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

