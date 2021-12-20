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
	const auto& enemys = FindGOs<Enemy>("enemy");//全てのエネミーの削除
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

	//背景
	m_skyCube->SetScale({ 300.0f, 300.0f, 300.0f });
	m_skyCube->SetType(enSkyCubeType_NightToon);
	m_skyCube->SetLuminance(0.5);

	//音声
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
	//レベル
	if (m_timer > 12.0f)
	{
		if (m_levelTimer <= 1.5) {
			m_levelTimer += 0.1f;
		}
		m_timer = 0;
	}

	//HPが0になるかプレイヤーがステージ外に落下した時
	if (m_hp->GetHP() == 0 || m_player->GetPosition().y <= -300.0f) {
		m_gameState = 1;
	}

	Timer();
	EnemyGenerate();
	MagicPointGenerate();
	PuddingGenerate();
}

void Game::Timer() 
{
	m_timer += g_gameTime->GetFrameDeltaTime();
	m_enemySpawnTimer += g_gameTime->GetFrameDeltaTime();
	m_magicPointSpawnTimer += g_gameTime->GetFrameDeltaTime();
	m_puddingSpawnTimer += g_gameTime->GetFrameDeltaTime();
}

void Game::EnemyGenerate()
{
	if (m_enemySpawnTimer > 2.0f - m_levelTimer)
	{
		constexpr int MIN = -500;//乱数の範囲最低値
		constexpr int MAX = 500;//乱数の範囲最大値

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
		constexpr int MIN = -500;//乱数の範囲最低値
		constexpr int MAX = 500;//乱数の範囲最大値

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
		constexpr int MIN = -500;//乱数の範囲最低値
		constexpr int MAX = 500;//乱数の範囲最大値

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

void Game::GameState()
{
	switch (m_gameState)
	{
		//ノーマル
	case 0:
		break;

		//スロー
	case 1:
		g_renderingEngine->SetIsGrayScale(true);
		break;

		//フィニッシュ
	case 2:
		break;

		//リザルト表示
	case 3:
		m_result = NewGO<Result>(0, "result");
		break;
	}
}