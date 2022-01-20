#pragma once

#include "Level3DRender/LevelRender.h"

class BackGround;
class Bullet;
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

	int GetManageState() const
	{
		return m_gameState;
	}
	Game();
	~Game();
	bool Start();
	void Update();
private:
	void Timer();
	void EnemyGenerate();
	void MagicPointGenerate();
	void PuddingGenerate();
	void ManageState();

private:

	//ï`âÊ
	ModelRender m_modelRender;

	//âπê∫
	SoundSource* m_backGroundBGM;

	//éQè∆
	Enemy* m_enemy;
	BackGround* m_backGround;
	Bullet* m_bullet;
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

	bool m_isStart = true;

	float m_timer = 0;
	float m_slowTimer = 0;
	float m_levelTimer = 0;
	float m_enemySpawnTimer = 0;
	float m_magicPointSpawnTimer = 0;
	float m_puddingSpawnTimer = 6.0;
	float m_stateTimer = 0.0f;

	int m_gameState = 0;
};

