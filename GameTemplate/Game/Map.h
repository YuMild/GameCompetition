#pragma once

class Player;

class Map :public IGameObject
{
public:
	Map();
	~Map();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender m_mapFrame;
	SpriteRender m_mapBackGround;
	SpriteRender m_playerMap;
	SpriteRender m_enemyMap;

	Vector3 m_playerMapPosition;

	Player* m_player;
};

