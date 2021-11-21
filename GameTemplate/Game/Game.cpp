#include "stdafx.h"
#include "Game.h"

#include "BackGround.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "GameOver.h"
#include "Ui.h"
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
	DeleteGO(m_gameCamera);
	DeleteGO(m_ui);
	DeleteGO(m_player);
	DeleteGO(m_skyCube);
}

bool Game::Start()
{
	m_backGround = NewGO<BackGround>(0, "backGround");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_ui = NewGO<Ui>(0, "ui");
	m_player = NewGO<Player>(0, "player");
	m_skyCube = NewGO<SkyCube>(0, "skyCube");

	//背景
	m_skyCube->SetScale({ 300.0f, 300.0f, 300.0f });
	m_skyCube->SetType(enSkyCubeType_NightToon);

	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/damage1.wav");
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/damage2.wav");
	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/damage3.wav");

	return true;
}

void Game::Update()
{
	m_timer += g_gameTime->GetFrameDeltaTime();
	m_spawnTimer += g_gameTime->GetFrameDeltaTime();

	EnemyGenerate();

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
	}

	//落下死亡//
	if (m_player->GetPosition().y <= -100.0f)
	{

		if (m_player->GetPosition().y <= -300.0f)
		{
			NewGO<GameOver>(0, "GameOver");
			DeleteGO(this);
		}
	}
}


void Game::EnemyGenerate()
{
	if (m_spawnTimer > 2.0f - m_level)
	{
		constexpr int MIN = -400;//乱数の範囲最低値
		constexpr int MAX = 400;//乱数の範囲最大値

		constexpr int RAND_NUMS_TO_GENERATE = 2;//乱数を生成する回数

		Vector3 position;
		//座標
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
		Enemy* enemy = NewGO<Enemy>(0, "Enemy");
		enemy->SetPosition(position);
		m_spawnTimer = 0.0f;
	}
}

void Game::Render(RenderContext& rc)
{
	
}