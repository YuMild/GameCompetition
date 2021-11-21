#pragma once

#include "Level3DRender/LevelRender.h"

class BackGround;
class Enemy;
class GameCamera;
class GameOver;
class Ui;
class Player;

class Game : public IGameObject
{
public:

	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void EnemyGenerate();
private:
	ModelRender m_modelRender;
	BackGround* m_backGround;
	GameCamera* m_gameCamera;
	GameOver* m_gameOver;
	Ui* m_ui;
	Player* m_player;
	SkyCube* m_skyCube;
	

	int m_levelFont = 0;

	float m_timer = 0;
	float m_level = 0;
	float m_spawnTimer = 0;
};

