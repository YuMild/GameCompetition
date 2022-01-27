#pragma once

class Game;
class Player;

/// <summary>
/// マップ
/// </summary>
class Map :public IGameObject
{
public:

	/// <summary>
	/// マップの中央の座標を取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetMapCenterPosition() const {
		return m_mapCenterPosition;
	}

	Map();
	~Map();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:

	SpriteRender m_mapBackGround;				//	背景
	SpriteRender m_mapGradation;				//	グラデーション
	SpriteRender m_mapFrame;					//	枠
	SpriteRender m_mapFrameGray;				//	枠のグレー
	SpriteRender m_playerMap;					//	プレイヤー
	SpriteRender m_playerMapGray;				//	プレイヤーのグレー

	Vector3 m_mapCenterPosition;
	Vector3 m_playerMapPosition;
	Vector3 m_playerMapGrayPosition;

	Game* m_game;
	Player* m_player;
};

