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

	void PuddingMap(RenderContext& rc)
	{
		if (m_isStart == false)
		{
			return;
		}
		m_puddingMap.Draw(rc);
	}
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
	bool Start();
	void Update();

private:

	/// <summary>
	/// マップ上の動作
	/// </summary>
	void MapMove();

	//画像
	SpriteRender m_puddingMap;
	SpriteRender m_puddingMapGray;

	//ベクトル
	Vector3 m_position;
	Vector3 m_diff;

	//エフェクト
	EffectEmitter* m_puddingEF;

	//サウンド
	SoundSource* m_puddingGetSE;

	//参照
	Game* m_game;
	Map* m_map;
	Player* m_player;
	Score* m_score;

	int m_getPudding = 0;

	float m_aliveTimer = 0;
};

