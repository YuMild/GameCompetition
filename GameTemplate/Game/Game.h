#pragma once

#include "Level3DRender/LevelRender.h"

class BackGround;
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
	ModelRender modelRender;

	BackGround* backGround;
	GameCamera* gameCamera;
	Map* map;
	Player* player;
};

