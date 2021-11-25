#pragma once

#include "Level3DRender/LevelRender.h"

class BackGround;
class Clock;
class Enemy;
class GameCamera;
class GameOver;
class Magic;
class Map;
class Mp;
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
	SoundSource* m_backGroundBGM;
	BackGround* m_backGround;
	Clock* m_clock;
	GameCamera* m_gameCamera;
	GameOver* m_gameOver;
	Magic* m_magic;
	Map* m_map;
	Mp* m_mp;
	Player* m_player;
	SkyCube* m_skyCube;

	int m_levelFont = 0;

	float m_timer = 0;
	float m_level = 0;
	float m_spawnTimer = 0;
};

