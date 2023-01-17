#pragma once

class Game;
class Map;
class Player;
class Score;

/// <summary>
/// プリン
/// </summary>
class Pudding :public IGameObject
{
public:

	/// <summary>
	/// 獲得したプリンの数を取得
	/// </summary>
	/// <returns></returns>
	int GetGetPudding() const
	{
		return m_getPudding;
	}

	/// <summary>
	/// 座標を指定
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(Vector3& position) {
		m_position = position;
	}

	/// <summary>
	/// マップ上に画像を生成する
	/// </summary>
	/// <param name="rc"></param>
	void PuddingMap(RenderContext& rc)
	{
		if (m_isStart == false)
		{
			return;
		}
		m_puddingMap.Draw(rc);
	}

	/// <summary>
	/// マップ上にグレー画像を生成する
	/// </summary>
	/// <param name="rc"></param>
	void  PuddingMapGray(RenderContext& rc)
	{
		if (m_isStart == false)
		{
			return;
		}
		m_puddingMapGray.Draw(rc);
	}

	Pudding();
	~Pudding();
	bool Start()override;
	void Update()override;

private:

	/// <summary>
	/// マップ上の動作
	/// </summary>
	void MapMove();

	//画像
	SpriteRender	m_puddingMap;
	SpriteRender	m_puddingMapGray;

	//ベクトル
	Vector3			m_position;
	Vector3			m_diff;

	//エフェクト
	EffectEmitter*	m_puddingEF				= nullptr;

	//サウンド
	SoundSource*	m_puddingGetSE			= nullptr;

	//参照
	Game*			m_game					= nullptr;
	Map*			m_map					= nullptr;
	Player*			m_player				= nullptr;
	Score*			m_score					= nullptr;

	int				m_getPudding			= 0;

	float			m_aliveTimer			= 0;
};

