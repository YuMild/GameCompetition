#pragma once

#include "Level3DRender/LevelRender.h"

class BackGround;
class Clock;
class Enemy;
class GameCamera;
class GameOver;
class Hp;
class Magic;
class MagicPoint;
class Map;
class Mp;
class Player;
class Score;

class Game : public IGameObject
{

public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Timer();
	void EnemyGenerate();
	void MagicPointGenerate();

private:

	//ï`âÊ
	ModelRender m_modelRender;

	//âπê∫
	SoundSource* m_backGroundBGM;

	//éQè∆
	Enemy* m_enemy;
	BackGround* m_backGround;
	Clock* m_clock;
	GameCamera* m_gameCamera;
	GameOver* m_gameOver;
	Hp* m_hp;
	Magic* m_magic;
	MagicPoint* m_magicPoint;
	Map* m_map;
	Mp* m_mp;
	Player* m_player;
	Score* m_score;
	SkyCube* m_skyCube;

	float m_timer = 0;
	float m_level = 0;
	float m_enemySpawnTimer = 0;
	float m_magicSpawnTimer = 0;
};

