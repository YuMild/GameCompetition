#pragma once

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

/// <summary>
/// GameState
/// </summary>
enum enGameState
{
	enGameState_PlayerAlive,
	enGameState_Slow,
	enGameState_GameFinish,
	enGameState_Result,
	enGameState_TimeScore,
	enGameState_PuddingScore,
	enGameState_TotalScore,
	enGameState_RankD,
	enGameState_RankC,
	enGameState_RankB,
	enGameState_RankA,
	enGameState_RankS
};

/// <summary>
/// SoundNumber
/// </summary>
enum enInitSoundNumber
{
	enInitSoundNumber_Title,
	enInitSoundNumber_BackGround,
	enInitSoundNumber_Bullet,
	enInitSoundNumber_Fire,
	enInitSoundNumber_Water,
	enInitSoundNumber_Wind,
	enInitSoundNumber_Shine,
	enInitSoundNumber_Damage_First,
	enInitSoundNumber_Damage_Second,
	enInitSoundNumber_Damage_Third,
	enInitSoundNumber_EnemyDeath,
	enInitSoundNumber_MagicPoint,
	enInitSoundNumber_Pudding,
	enInitSoundNumber_DrumRoll,
	enInitSoundNumber_Drum,
	enInitSoundNumber_Button,
};

/// <summary>
/// EffectNumber
/// </summary>
enum enInitEffectNumber
{
	enInitEffectNumber_Bullet,
	enInitEffectNumber_Fire,
	enInitEffectNumber_Water,
	enInitEffectNumber_Wind,
	enInitEffectNumber_Shine,
	enInitEffectNumber_CoolTimeCompleteFire,
	enInitEffectNumber_CoolTimeCompleteWater,
	enInitEffectNumber_CoolTimeCompleteWind,
	enInitEffectNumber_CoolTimeCompleteShine,
	enInitEffectNumber_MagicCircleFire,
	enInitEffectNumber_MagicCircleWater,
	enInitEffectNumber_MagicCircleWind,
	enInitEffectNumber_MagicCircleShine,
	enInitEffectNumber_MagicPoint,
	enInitEffectNumber_MagicPointDelete,
	enInitEffectNumber_Pudding,
	enInitEffectNumber_EnemyDeath,
};

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
	ModelRender			m_modelRender;

	//音声
	SoundSource*		m_backGroundBGM;

	//参照
	Enemy*				m_enemy					= nullptr;
	BackGround*			m_backGround			= nullptr;
	Bullet*				m_bullet				= nullptr;
	Clock*				m_clock					= nullptr;
	GameCamera*			m_gameCamera			= nullptr;
	Hp*					m_hp					= nullptr;
	Magic*				m_magic					= nullptr;
	MagicPoint*			m_magicPoint			= nullptr;
	Map*				m_map					= nullptr;
	Mp*					m_mp					= nullptr;
	Player*				m_player				= nullptr;
	Pudding*			m_pudding				= nullptr;
	Result*				m_result				= nullptr;
	Score*				m_score					= nullptr;
	SkyCube*			m_skyCube				= nullptr;

	bool				m_isStart				= true;					//	一度だけ判定を取る

	float				m_timer					= 0;					//	全体のタイマー
	float				m_level					= 0;					//	レベルアップ
	float				m_enemySpawnTimer		= 0;					//	敵機のスポーン
	float				m_magicPointSpawnTimer	= 0;					//	MagicPointのスポーン
	float				m_puddingSpawnTimer		= 6.0;					//	プリンのスポーン
	float				m_stateTimer			= 0.0f;					//	Stateの移行

	int					m_gameState				= 0;					//	シーンの移行
};

