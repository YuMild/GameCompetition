#include "stdafx.h"
#include "Game.h"

#include "BackGround.h"
#include "Clock.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "GameOver.h"
#include "Magic.h"
#include "MagicPoint.h"
#include "Map.h"
#include "Mp.h"
#include "Player.h"

#include "nature/SkyCube.h"

#include <random>

using namespace std;

Game::Game() {

}

Game::~Game() {
	const auto& enemys = FindGOs<Enemy>("Enemy");//全てのエネミーの削除
	int size = enemys.size();
	for (int i = 0; i < size; i++)
	{
		DeleteGO(enemys[i]);
	}
	DeleteGO(m_backGround);
	DeleteGO(m_backGroundBGM);
	DeleteGO(m_clock);
	DeleteGO(m_gameCamera);
	DeleteGO(m_magic);
	DeleteGO(m_map);
	DeleteGO(m_mp);
	DeleteGO(m_player);
	DeleteGO(m_skyCube);
}

bool Game::Start()
{
	m_backGround = NewGO<BackGround>(0, "backGround");
	m_clock = NewGO<Clock>(0, "clock");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_magic = NewGO<Magic>(0, "magic");
	m_map = NewGO<Map>(0, "map");
	m_mp = NewGO<Mp>(0, "Mp");
	m_player = NewGO<Player>(0, "player");
	m_skyCube = NewGO<SkyCube>(0, "skyCube");

	//背景
	m_skyCube->SetScale({ 300.0f, 300.0f, 300.0f });
	m_skyCube->SetType(enSkyCubeType_NightToon);
	m_skyCube->SetLuminance(0.5);

	//音声
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/BackGround.wav");
	m_backGroundBGM = NewGO<SoundSource>(1);
	m_backGroundBGM->Init(1);
	m_backGroundBGM->Play(true);
	g_sceneLight->SetDirectionLight(0, Vector3(0.5f,-0.5f,0.5f), Vector3(2.5f,2.5f,2.5f));
	return true;
}

void Game::Update()
{
	m_timer += g_gameTime->GetFrameDeltaTime();
	m_enemySpawnTimer += g_gameTime->GetFrameDeltaTime();
	m_magicSpawnTimer += g_gameTime->GetFrameDeltaTime();

	//レベル
	if (m_timer > 10.0f)
	{
		if (m_level <= 1.5) {
			m_level += 0.1f;
		}
		m_levelFont += 1;
		m_timer = 0;
	}

	if (m_player->GetHP() == 0) {
		m_gameOver = NewGO<GameOver>(0, "GameOver");
		DeleteGO(this);
	}

	//落下死亡//
	if (m_player->GetPosition().y <= -300.0f)
	{
		NewGO<GameOver>(0, "GameOver");
		DeleteGO(this);
	}

	EnemyGenerate();
	MagicPointGenerate();
}

void Game::EnemyGenerate()
{
	if (m_enemySpawnTimer > 2.0f - m_level)
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

		if ((position - m_player->GetPosition()).Length() <= 20.0f)
		{
			return;
		}
		m_enemy = NewGO<Enemy>(0, "Enemy");
		m_enemy->SetPosition(position);
		m_enemySpawnTimer = 0.0f;
	}
}

void Game::MagicPointGenerate()
{
	if (m_magicSpawnTimer > 15.0f)
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

		if ((position - m_player->GetPosition()).Length() <= 20.0f)
		{
			return;
		}
		m_magicPoint = NewGO<MagicPoint>(0, "magicPoint");
		m_magicPoint->SetPosition(position);
		m_magicSpawnTimer = 0.0f;
	}
}

