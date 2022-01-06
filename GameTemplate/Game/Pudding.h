#pragma once

class Game;
class Map;
class Player;
class Score;

class Pudding :public IGameObject
{
public:

	int GetGetPudding() const
	{
		return m_getPudding;
	}
	void SetPosition(Vector3& position) {
		m_position = position;
	}
	Pudding();
	~Pudding();
	bool Start();
	void Update();
	void MapMove();
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

private:

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

