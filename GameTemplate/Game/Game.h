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
	/// ManageState�̒l�𓾂�
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
	/// �������̔���
	/// </summary>
	void Fall();

	/// <summary>
	/// ���Ԃ̉��Z
	/// </summary>
	void Timer();

	/// <summary>
	/// �G�@�𔭐�������
	/// </summary>
	void EnemyGenerate();

	/// <summary>
	/// MagicPoint�𔭐�������
	/// </summary>
	void MagicPointGenerate();

	/// <summary>
	/// �v�����𔭐�������
	/// </summary>
	void PuddingGenerate();

	/// <summary>
	/// Manage���Ǘ�����
	/// </summary>
	void ManageState();

private:

	//�`��
	ModelRender			m_modelRender;

	//����
	SoundSource*		m_backGroundBGM;

	//�Q��
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

	bool				m_isStart				= true;					//	��x������������

	float				m_timer					= 0;					//	�S�̂̃^�C�}�[
	float				m_level					= 0;					//	���x���A�b�v
	float				m_enemySpawnTimer		= 0;					//	�G�@�̃X�|�[��
	float				m_magicPointSpawnTimer	= 0;					//	MagicPoint�̃X�|�[��
	float				m_puddingSpawnTimer		= 6.0;					//	�v�����̃X�|�[��
	float				m_stateTimer			= 0.0f;					//	State�̈ڍs

	int					m_gameState				= 0;					//	�V�[���̈ڍs
};

