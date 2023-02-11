#include "stdafx.h"
#include "Game.h"
#include "BackGround.h"
#include "Bullet.h"
#include "Clock.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "Hp.h"
#include "Magic.h"
#include "MagicPoint.h"
#include "Map.h"
#include "Mp.h"
#include "Player.h"
#include "Pudding.h"
#include "Result.h"
#include "Score.h"

#include "nature/SkyCube.h"

#include <random>

using namespace std;

namespace
{
	const float SKYCUBE_SIZE				= 300.0f;													//	�X�J�C�L���[�u�̃T�C�Y
	const float BGM_VOLUME					= 0.5f;														//�@BGM�̉���
	const float FALL_LINE					= -100.0f;													//�@�������̔��胉�C��
	const float LEVELUP_TIME				= 12.0f;													//�@���x���A�b�v�̊Ԋu
	const float ENEMY_SPAWNTIME				= 1.8f;														//�@�G�l�~�[�̃X�|�[���Ԋu
	const float PUDDING_SPAWNTIME			= 12.0f;													//�@�v�����̃X�|�[���Ԋu
	const float MAGICPOINT_SPAWNTIME		= 12.0f;													//�@MagicPoint�̃X�|�[���Ԋu
	const Vector3 DIRECTIONLIGHT_DIRECTION	= { 0.5f, -0.5f, 0.5f };									//�@���C�g�̎ˏo����
	const Vector3 DIRECTIONLIGHT_COLOR		= { 2.5f,2.5f,2.5f };										//�@���C�g�̐F
}

Game::Game()
{

}

Game::~Game()
{
    g_renderingEngine->SetIsAllGrayScale(false);														//	�O���[�X�P�[����OFF��
	g_k2Engine->GetK2EngineLow()->SetFrameRateMode(K2EngineLow::enFrameRateMode_Variable, 60.0f);		//	FPS�����ɖ߂�

	//	DeleteGO
	DeleteGO(m_backGround);																				//	BackGround
	DeleteGO(m_backGroundBGM);																			//	BGM
	const auto& bullets = FindGOs<Bullet>("bullet");													//	Bullet
	for (auto& Bullet : bullets)
	{
		DeleteGO(Bullet);
	}
	DeleteGO(m_clock);																					//	Clock
	const auto& enemys = FindGOs<Enemy>("enemy");														//	Enemy
	for (auto& Enemy : enemys)
	{
		DeleteGO(Enemy);
	}
	DeleteGO(m_gameCamera);																				//	GameCamera
	DeleteGO(m_hp);																						//	HP
	DeleteGO(m_magic);																					//	Magic
	const auto& magicPoints = FindGOs<MagicPoint>("magicPoint");										//	MagicPoint
	for (auto& MagicPoint : magicPoints)
	{
		DeleteGO(MagicPoint);
	}
	DeleteGO(m_map);																					//	Map
	DeleteGO(m_mp);																						//	MP
	DeleteGO(m_player);																					//	Player
	DeleteGO(m_pudding);																				//	Pudding
	DeleteGO(m_score);																					//	Score
	DeleteGO(m_skyCube);																				//	SkyCube
}

bool Game::Start()
{
	//	NewGO
	m_backGround	= NewGO<BackGround>(0, "backGround");												//	BackGround
	m_clock			= NewGO<Clock>(0, "clock");															//	Clock
	m_gameCamera	= NewGO<GameCamera>(0, "gameCamera");												//	GameCamera
	m_hp			= NewGO<Hp>(0, "hp");																//	HP
	m_magic			= NewGO<Magic>(0, "magic");															//	Magic
	m_map			= NewGO<Map>(0, "map");																//	Map
	m_mp			= NewGO<Mp>(0, "mp");																//	MP
	m_player		= NewGO<Player>(0, "player");														//	Player
	m_score			= NewGO<Score>(0, "score");															//	Score
	m_skyCube		= NewGO<SkyCube>(0, "skyCube");														//	SkyCube

	//	�w�i
	m_skyCube->SetScale(Vector3::One * 300.0f);															//	�T�C�Y
	m_skyCube->SetType(enSkyCubeType_NightToon);														//	SkyCube�̎��
	m_skyCube->SetLuminance(0.5);																		//	�P�x

	//	����
	g_soundEngine->ResistWaveFileBank(enInitSoundNumber_BackGround, "Assets/sound/BackGround.wav");		//	BGM
	m_backGroundBGM = NewGO<SoundSource>(0);
	m_backGroundBGM->Init(enInitSoundNumber_BackGround);
	m_backGroundBGM->SetVolume(BGM_VOLUME);
	m_backGroundBGM->Play(true);

	// ���C�g
	g_sceneLight->SetDirectionLight(0, DIRECTIONLIGHT_DIRECTION, DIRECTIONLIGHT_COLOR);					//	�f�B���N�V�������C�g
	
	return true;
}

void Game::Update()
{
	Fall();
	ManageState();
	if (m_hp->GetHP() == 0)																				//	�v���C���[��HP��0�̎�
	{
		return;																							//	�֐��̏������I��������
	}
	EnemyGenerate();
	MagicPointGenerate();
	PuddingGenerate();
	Timer();
}

void Game::Fall()
{
	//�@�X�e�[�W�O�ɗ���������HP��0�ɂ���
	if (m_player->GetPosition().y <= FALL_LINE)
	{
		m_hp->SetHP(0);
	}
}

void Game::Timer() 
{
	m_timer += g_gameTime->GetFrameDeltaTime();
	m_enemySpawnTimer += g_gameTime->GetFrameDeltaTime();
	m_magicPointSpawnTimer += g_gameTime->GetFrameDeltaTime();
	m_puddingSpawnTimer += g_gameTime->GetFrameDeltaTime();

	//	���x���A�b�v
	if (m_timer > LEVELUP_TIME)
	{
		//�@���x�����グ��(�����15)
		if (m_level < 15) {
			m_level += 1;
		}
		m_timer = 0.0f;
	}
}

void Game::EnemyGenerate()
{
	if (m_enemySpawnTimer > ENEMY_SPAWNTIME - m_level / 10)
	{
		constexpr int MIN = -500;																		//	�����͈͍̔Œ�l
		constexpr int MAX = 500;																		//	�����͈͍̔ő�l

		Vector3 position;
		random_device rd;
		default_random_engine eng(rd());
		uniform_int_distribution<int> distr(MIN, MAX);

		position.x = distr(eng);
		position.z = distr(eng);
		position.y = 0.0f;

		m_enemy = NewGO<Enemy>(0, "enemy");
		m_enemy->SetPosition(position);
		m_enemySpawnTimer = 0.0f;
	}
}

void Game::MagicPointGenerate()
{
	if (m_magicPointSpawnTimer > MAGICPOINT_SPAWNTIME)
	{
		constexpr int MIN = -500;																		//	�����͈͍̔Œ�l
		constexpr int MAX = 500;																		//	�����͈͍̔ő�l

		Vector3 position;
		random_device rd;
		default_random_engine eng(rd());
		uniform_int_distribution<int> distr(MIN, MAX);													//	MIN��MAX�̊ԂŃ����_���Ȓl���쐬

		position.x = distr(eng);
		position.z = distr(eng);
		position.y = 0.0f;

		m_magicPoint = NewGO<MagicPoint>(0, "magicPoint");
		m_magicPoint->SetPosition(position);
		m_magicPointSpawnTimer = 0.0f;																	//	�^�C�}�[�̃��Z�b�g
	}
}

void Game::PuddingGenerate()
{
	if (m_puddingSpawnTimer > PUDDING_SPAWNTIME)
	{
		constexpr int MIN = -500;																		//	�����͈͍̔Œ�l
		constexpr int MAX = 500;																		//	�����͈͍̔ő�l

		Vector3 position;
		random_device rd;
		default_random_engine eng(rd());
		uniform_int_distribution<int> distr(MIN, MAX);													//	MIN��MAX�̊ԂŃ����_���Ȓl���쐬

		position.x = distr(eng);
		position.z = distr(eng);
		position.y = 0.0f;

		m_pudding = NewGO<Pudding>(0, "pudding");
		m_pudding->SetPosition(position);
		m_puddingSpawnTimer = 0.0f;																		//�@�^�C�}�[�̃��Z�b�g
	}
}

void Game::ManageState()
{
	//	���S��
	if (m_gameState != enGameState_PlayerAlive)
	{
		m_stateTimer += g_gameTime->GetFrameDeltaTime();												//	���Ԍo��
	}

	switch (m_gameState)
	{

	//	������
	case enGameState_PlayerAlive:

		if (m_hp->GetHP() == 0)																			//	HP��0�ɂȂ邩�v���C���[���X�e�[�W�O�ɗ���������
		{
			m_player->SetState(3);																		//	�v���C���[�̎��S�A�j���[�V�������Đ�������
			m_gameState = enGameState_Slow;																//	�X���[�Ɉڍs
			m_backGroundBGM->Stop();																	//	BGM���X�g�b�v������
		}
		break;

	//	�X���[��
	case enGameState_Slow:

		g_renderingEngine->SetIsAllGrayScale(true);														//	���m�N��
		g_k2Engine->GetK2EngineLow()->SetFrameRateMode(K2EngineLow::enFrameRateMode_Variable, 20.0f);	//	FPS��������
		if (m_stateTimer >= 2.0f)																		//	�t�B�j�b�V���܂ł̃J�E���g�A�b�v
		{
			m_gameState = enGameState_GameFinish;														//	�t�B�j�b�V���Ɉڍs
			m_stateTimer = 0.0f;																		//	�^�C�}�[�̃��Z�b�g
		}
		break;

	//	�t�B�j�b�V����
	case enGameState_GameFinish:

		if (m_stateTimer >= 1.5f)																		//	���U���g�܂ł̃J�E���g�A�b�v
		{
			m_gameState = enGameState_Result;															//	���U���g�Ɉڍs
			m_stateTimer = 0.0f;																		//	�^�C�}�[�̃��Z�b�g
		}
		break;

	//	���U���g��
	case enGameState_Result:

		if (m_isStart == true)																			//	��x�������s
		{
			m_result = NewGO<Result>(0, "result");
			m_isStart = false;
		}
		if (m_stateTimer >= 1.0f)
		{
			m_gameState = enGameState_TimeScore;														//	�^�C���X�R�A�Ɉڍs
			m_stateTimer = 0.0f;																		//	�^�C�}�[�̃��Z�b�g
		}
		break;

	//	�^�C���X�R�A�\��
	case enGameState_TimeScore:

		if (m_stateTimer >= 0.8f)
		{
			m_gameState = enGameState_PuddingScore;														//	�v�����X�R�A�Ɉڍs
			m_stateTimer = 0.0f;																		//	�^�C�}�[�̃��Z�b�g
		}
		break;

	//	�v�����X�R�A�\��
	case enGameState_PuddingScore:

		if (m_stateTimer >= 0.8f)
		{
			m_gameState = enGameState_TotalScore;														//	�g�[�^���X�R�A�Ɉڍs
			m_stateTimer = 0.0f;																		//	�^�C�}�[�̃��Z�b�g
		}
		break;

	//	�g�[�^���X�R�A�\��
	case enGameState_TotalScore:
		if (m_stateTimer >= 1.5f)
		{
			//	D�����N
			if (m_score->GetTotalScoreOld() < 5000.0f)
			{
				m_gameState = enGameState_RankD;
				m_stateTimer = 0.0f;																	//	�^�C�}�[�̃��Z�b�g
			}
			//	C�����N
			else if (m_score->GetTotalScoreOld() > 5001.0f && m_score->GetTotalScoreOld() < 10000.0f)
			{
				m_gameState = enGameState_RankC;
				m_stateTimer = 0.0f;																	//	�^�C�}�[�̃��Z�b�g
			}
			//	B�����N
			else if (m_score->GetTotalScoreOld() > 10001.0f && m_score->GetTotalScoreOld() < 15000.0f)
			{
				m_gameState = enGameState_RankB;
				m_stateTimer = 0.0f;																	//	�^�C�}�[�̃��Z�b�g
			}
			//	A�����N
			else if (m_score->GetTotalScoreOld() > 15001.0f && m_score->GetTotalScoreOld() < 20000.0f)
			{
				m_gameState = enGameState_RankA;
				m_stateTimer = 0.0f;																	//	�^�C�}�[�̃��Z�b�g
			}
			//	S�����N
			else if (m_score->GetTotalScoreOld() > 20001.0f)
			{
				m_gameState = enGameState_RankS;
				m_stateTimer = 0.0f;																	//	�^�C�}�[�̃��Z�b�g
			}
		}
			
		break;
	}
}