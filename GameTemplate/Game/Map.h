#pragma once

class Enemy;
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
	//SpriteRender m_enemysMap[30];
	SpriteRender m_mapBackGround;
	SpriteRender m_mapGradation;
	SpriteRender m_mapFrame;
	SpriteRender m_playerMap;

	Vector3 m_playerMapPosition;
	Vector3 m_enemyMapPosition;

	Enemy* m_enemy;
	Player* m_player;
};

