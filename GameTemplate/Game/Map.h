#pragma once

class Game;
class Player;

class Map :public IGameObject
{
public:
	Vector3 GetMapCenterPosition() const {
		return m_mapCenterPosition;
	}
	Map();
	~Map();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender m_mapBackGround;
	SpriteRender m_mapGradation;
	SpriteRender m_mapFrame;
	SpriteRender m_mapFrameGray;
	SpriteRender m_playerMap;
	SpriteRender m_playerMapGray;

	Vector3 m_mapCenterPosition;
	Vector3 m_playerMapPosition;
	Vector3 m_playerMapGrayPosition;

	Game* m_game;
	Player* m_player;
};

