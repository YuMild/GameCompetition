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
	ModelRender m_modelRender;

	//����
	SoundSource* m_backGroundBGM;

	//�Q��
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

	bool m_isStart = true;												//��x������������

	float m_timer = 0;													//�S�̂̃^�C�}�[
	float m_levelTimer = 0;												//���x���A�b�v
	float m_enemySpawnTimer = 0;										//�G�@�̃X�|�[��
	float m_magicPointSpawnTimer = 0;									//MagicPoint�̃X�|�[��
	float m_puddingSpawnTimer = 6.0;									//�v�����̃X�|�[��
	float m_stateTimer = 0.0f;											//State�̈ڍs

	int m_gameState = 0;												//�V�[���̈ڍs
};

