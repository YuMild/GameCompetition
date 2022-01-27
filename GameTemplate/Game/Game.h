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

	/// <summary>
	/// ManageStateの値を得る
	/// </summary>
	/// <returns></returns>
	int GetManageState() const
	{
		return m_gameState;
	}

	Game();
	~Game();
	bool Start();
	void Update();

private:

	/// <summary>
	/// 落下死の判定
	/// </summary>
	void Fall();

	/// <summary>
	/// 時間の加算
	/// </summary>
	void Timer();

	/// <summary>
	/// 敵機を発生させる
	/// </summary>
	void EnemyGenerate();

	/// <summary>
	/// MagicPointを発生させる
	/// </summary>
	void MagicPointGenerate();

	/// <summary>
	/// プリンを発生させる
	/// </summary>
	void PuddingGenerate();

	/// <summary>
	/// Manageを管理する
	/// </summary>
	void ManageState();

private:

	//描画
	ModelRender m_modelRender;

	//音声
	SoundSource* m_backGroundBGM;

	//参照
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

	bool m_isStart = true;												//一度だけ判定を取る

	float m_timer = 0;													//全体のタイマー
	float m_levelTimer = 0;												//レベルアップ
	float m_enemySpawnTimer = 0;										//敵機のスポーン
	float m_magicPointSpawnTimer = 0;									//MagicPointのスポーン
	float m_puddingSpawnTimer = 6.0;									//プリンのスポーン
	float m_stateTimer = 0.0f;											//Stateの移行

	int m_gameState = 0;												//シーンの移行
};

