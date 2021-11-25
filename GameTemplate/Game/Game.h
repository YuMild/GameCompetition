#pragma once

#include "Level3DRender/LevelRender.h"

class BackGround;
class Clock;
class Enemy;
class GameCamera;
class GameOver;
class Magic;
class MagicPoint;
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
	void EnemyGenerate();
	void MagicPointGenerate();
private:
	ModelRender m_modelRender;
	SoundSource* m_backGroundBGM;
	Enemy* m_enemy;
	BackGround* m_backGround;
	Clock* m_clock;
	GameCamera* m_gameCamera;
	GameOver* m_gameOver;
	Magic* m_magic;
	MagicPoint* m_magicPoint;
	Map* m_map;
	Mp* m_mp;
	Player* m_player;
	SkyCube* m_skyCube;

	int m_levelFont = 0;

	float m_timer = 0;
	float m_level = 0;
	float m_enemySpawnTimer = 0;
	float m_magicSpawnTimer = 0;
};

