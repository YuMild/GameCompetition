#pragma once

#include "Level3DRender/LevelRender.h"

class BackGround;
class Clock;
class Enemy;
class GameCamera;
class Hp;
class Magic;
class MagicPoint;
class Map;
class Mp;
class Player;
class Pudding;
class Result;
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
	void PuddingGenerate();
	void GameState();

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
	Hp* m_hp;
	Magic* m_magic;
	MagicPoint* m_magicPoint;
	Map* m_map;
	Mp* m_mp;
	Player* m_player;
	Pudding* m_pudding;
	Result* m_result;
	Score* m_score;
	SkyCube* m_skyCube;

	float m_timer = 0;
	float m_slowTimer = 0;
	float m_levelTimer = 0;
	float m_enemySpawnTimer = 0;
	float m_magicPointSpawnTimer = 0;
	float m_puddingSpawnTimer = 6.0;

	int m_gameState = 0;
};

