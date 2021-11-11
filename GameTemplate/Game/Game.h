#pragma once

#include "Level3DRender/LevelRender.h"

class BackGround;
class GameCamera;
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
	Player* player;
};

