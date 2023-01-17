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
	bool Start()override;
	void Update()override;

private:

	/// <summary>
	/// マップ上の動作を管理
	/// </summary>
	void MapMove();

	/// <summary>
	/// 音声を再生
	/// </summary>
	void PlayMagicPointDeleteEffect();

	//画像
	SpriteRender		m_magicPointMap;
	SpriteRender		m_magicPointMapGray;

	//ベクトル
	Vector3				m_position;
	Vector3				m_diff;

	//エフェクト
	EffectEmitter*		m_magicPointEF			= nullptr;
	EffectEmitter*		m_magicPointDeleteEF	= nullptr;

	//サウンド
	SoundSource*		m_magicPointSE			= nullptr;

	//参照
	Map*				m_map					= nullptr;
	Mp*					m_mp					= nullptr;
	Player*				m_player				= nullptr;

	float				m_aliveTimer			= 0;
};

