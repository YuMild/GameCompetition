#include "stdafx.h"
#include "Game.h"
#include "BackGround.h"
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

Game::Game()
{
}

Game::~Game()
{
	//DeleteGO
	DeleteGO(m_backGround);
	DeleteGO(m_backGroundBGM);
	DeleteGO(m_clock);
	const auto& enemys = FindGOs<Enemy>("enemy");//�S�ẴG�l�~�[�̍폜
	int enemySize = enemys.size();
	for (int i = 0; i < enemySize; i++)
	{
		DeleteGO(enemys[i]);
	}
	DeleteGO(m_gameCamera);
	DeleteGO(m_hp);
	DeleteGO(m_magic);
	/*const auto& magicPoints = FindGOs<MagicPoint>("magicPoint");
	int magicPointSize = magicPoints.size();
	for (int i = 0; i < enemySize; i++)
	{
		DeleteGO(magicPoints[i]);
	}*/
	DeleteGO(m_magicPoint);
	DeleteGO(m_map);
	DeleteGO(m_mp);
	DeleteGO(m_player);
	DeleteGO(m_pudding);
	//DeleteGO(m_score);
	DeleteGO(m_skyCube);
}

bool Game::Start()
{
	//NewGO
	m_backGround = NewGO<BackGround>(0, "backGround");
	m_clock = NewGO<Clock>(0, "clock");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_hp = NewGO<Hp>(0, "hp");
	m_magic = NewGO<Magic>(0, "magic");
	m_map = NewGO<Map>(0, "map");
	m_mp = NewGO<Mp>(0, "mp");
	m_player = NewGO<Player>(0, "player");
	m_score = NewGO<Score>(0, "score");
	m_skyCube = NewGO<SkyCube>(0, "skyCube");

	//�w�i
	m_skyCube->SetScale({ 300.0f, 300.0f, 300.0f });
	m_skyCube->SetType(enSkyCubeType_NightToon);
	m_skyCube->SetLuminance(0.5);

	//����
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/BackGround.wav");
	m_backGroundBGM = NewGO<SoundSource>(1);
	m_backGroundBGM->Init(1);
	m_backGroundBGM->SetVolume(0.5f);
	m_backGroundBGM->Play(true);
	g_sceneLight->SetDirectionLight(0, Vector3(0.5f,-0.5f,0.5f), Vector3(2.5f,2.5f,2.5f));

	EffectEngine::GetInstance()->ResistEffect2D(0, u"Assets/effect/MagicCircleFire.efk");
	
	return true;
}

void Game::Update()
{
	if (m_player->GetPosition().y <= -100.0f)
	{
		m_hp->SetHP(0);
	}


	if (m_hp->GetHP() >= 1) {
		EnemyGenerate();
		MagicPointGenerate();
		PuddingGenerate();
		Timer();
	}
	ManageState();
}

void Game::Timer() 
{
	//���x��
	if (m_timer > 12.0f)
	{
		if (m_levelTimer <= 1.5) {
			m_levelTimer += 0.1f;
		}
		m_timer = 0;
	}
	m_timer += g_gameTime->GetFrameDeltaTime();
	m_enemySpawnTimer += g_gameTime->GetFrameDeltaTime();
	m_magicPointSpawnTimer += g_gameTime->GetFrameDeltaTime();
	m_puddingSpawnTimer += g_gameTime->GetFrameDeltaTime();
}

void Game::EnemyGenerate()
{
	if (m_enemySpawnTimer > 2.0f - m_levelTimer)
	{
		constexpr int MIN = -500;//�����͈͍̔Œ�l
		constexpr int MAX = 500;//�����͈͍̔ő�l

		Vector3 position;
		random_device rd;
		default_random_engine eng(rd());
		uniform_int_distribution<int> distr(MIN, MAX);

		position.x = distr(eng);
		position.z = distr(eng);
		position.y = 0.0f;

		if ((position - m_player->GetPosition()).Length() <= 100.0f)
		{
			return;
		}

		m_enemy = NewGO<Enemy>(0, "enemy");
		m_enemy->SetPosition(position);
		m_enemySpawnTimer = 0.0f;
	}
}

void Game::MagicPointGenerate()
{
	if (m_magicPointSpawnTimer > 12.0f)
	{
		constexpr int MIN = -500;//�����͈͍̔Œ�l
		constexpr int MAX = 500;//�����͈͍̔ő�l

		Vector3 position;
		random_device rd;
		default_random_engine eng(rd());
		uniform_int_distribution<int> distr(MIN, MAX);

		position.x = distr(eng);
		position.z = distr(eng);
		position.y = 0.0f;

		if ((position - m_player->GetPosition()).Length() <= 50.0f)
		{
			return;
		}

		m_magicPoint = NewGO<MagicPoint>(0, "magicPoint");
		m_magicPoint->SetPosition(position);
		m_magicPointSpawnTimer = 0.0f;
	}
}

void Game::PuddingGenerate()
{
	if (m_puddingSpawnTimer > 12.0f)
	{
		constexpr int MIN = -500;//�����͈͍̔Œ�l
		constexpr int MAX = 500;//�����͈͍̔ő�l

		Vector3 position;
		random_device rd;
		default_random_engine eng(rd());
		uniform_int_distribution<int> distr(MIN, MAX);

		position.x = distr(eng);
		position.z = distr(eng);
		position.y = 0.0f;

		if ((position - m_player->GetPosition()).Length() <= 50.0f)
		{
			return;
		}

		m_pudding = NewGO<Pudding>(0, "pudding");
		m_pudding->SetPosition(position);
		m_puddingSpawnTimer = 0.0f;
	}
}

void Game::ManageState()
{
	if (m_gameState >= 1)
	{
		m_stateTimer += g_gameTime->GetFrameDeltaTime();
	}

	switch (m_gameState)
	{
	case 0://������
		if (m_hp->GetHP() == 0) //HP��0�ɂȂ邩�v���C���[���X�e�[�W�O�ɗ���������
		{
			m_player->SetState(3);
			m_gameState = 1;
			m_backGroundBGM->Stop();
		}
		break;

	case 1://�X���[��

		//���m�N��
		g_renderingEngine->SetIsAllGrayScale(true);

		//FPS��������
		g_k2Engine->GetK2EngineLow()->SetFrameRateMode(K2EngineLow::enFrameRateMode_Variable, 20.0f);

		//�t�B�j�b�V���܂ł̃J�E���g�A�b�v

		if (m_stateTimer >= 2.0f)
		{
			m_gameState = 2;
			m_stateTimer = 0.0f;
		}
		break;

	case 2://�t�B�j�b�V����

		//���U���g�܂ł̃J�E���g�A�b�v

		if (m_stateTimer >= 1.5f)
		{
			m_gameState = 3;
			m_stateTimer = 0.0f;
		}
		break;

	case 3://���U���g�\��

		if (m_isStart == true)
		{
			m_result = NewGO<Result>(0, "result");
			m_isStart = false;
		}

		if (m_stateTimer >= 1.0f)
		{
			m_gameState = 4; m_stateTimer = 0.0f;
		}

		break;

	case 4://�^�C���X�R�A�\��

		if (m_stateTimer >= 0.8f)
		{
			m_gameState = 5; m_stateTimer = 0.0f;
		}

		break;

	case 5://�v�����X�R�A�\��

		if (m_stateTimer >= 0.8f)
		{
			m_gameState = 6; m_stateTimer = 0.0f;
		}

		break;

	case 6://�g�[�^���X�R�A�\��

		if (m_stateTimer >= 1.5f)
		{
			if (m_score->GetTotalScoreOld() < 5000.0f)//D�����N
			{
				m_gameState = 7; m_stateTimer = 0.0f;
			}

			else if (m_score->GetTotalScoreOld() > 5001.0f && m_score->GetTotalScoreOld() < 10000.0f)//C�����N
			{
				m_gameState = 8; m_stateTimer = 0.0f;
			}

			else if (m_score->GetTotalScoreOld() > 10001.0f && m_score->GetTotalScoreOld() < 15000.0f)//B�����N
			{
				m_gameState = 9; m_stateTimer = 0.0f;
			}

			else if (m_score->GetTotalScoreOld() > 15001.0f && m_score->GetTotalScoreOld() < 20000.0f)//A�����N
			{
				m_gameState = 10; m_stateTimer = 0.0f;
			}

			else if (m_score->GetTotalScoreOld() > 20001.0f)//S�����N
			{
				m_gameState = 11; m_stateTimer = 0.0f;
			}
		}

		break;
	}
}