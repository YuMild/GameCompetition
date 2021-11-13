#pragma once

#include "Level3DRender/LevelRender.h"

class BackGround;
class Enemy;
class GameCamera;
class Map;
class Player;

class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	ModelRender m_modelRender;
	BackGround* m_backGround;
	GameCamera* m_gameCamera;
	Map* m_map;
	Player* m_player;
	int hp = 3;
	float m_level = 0;
	float m_spawnTimer = 0;
};

