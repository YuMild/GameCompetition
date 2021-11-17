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
	const auto& enemys = FindGOs<Enemy>("Enemy");//�S�ẴG�l�~�[�̍폜
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

	//�w�i
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

	//���x��
	if (m_timer > 10.0f)
	{
		if (m_level <= 1.5) {
			m_level += 0.1f;
		}
		m_levelFont += 1;
		m_timer = 0;
	}

	//���S����//
	const auto& enemyList = FindGOs<Enemy>("Enemy");
	for (auto enemy : enemyList)
	{
		Vector3 unitydiff = m_player->GetPosition() - enemy->GetPosition();
		if (unitydiff.Length() <= 10.0f) {
			if (m_hp >= 1) {
				m_hp -= 1;
				DeleteGO(enemy);
			}
			if (m_hp == 0) {
				m_gameOver = NewGO<GameOver>(0, "GameOver");
			}
		}
	}
	//�������S//
	if (m_player->GetPosition().y <= -100.0f)
	{

		if (m_player->GetPosition().y <= -300.0f)
		{
			NewGO<GameOver>(0, "GameOver");
			DeleteGO(this);
		}
	}

	ManageState();
}

void Game::EnemyGenerate()
{
	if (m_spawnTimer > 2.0f - m_level)
	{
		constexpr int MIN = -400;//�����͈͍̔Œ�l
		constexpr int MAX = 400;//�����͈͍̔ő�l

		constexpr int RAND_NUMS_TO_GENERATE = 2;//�����𐶐������

		Vector3 position;
		//���W
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

void Game::ManageState() 
{
	switch (m_hp) {
	case 0:
		if (m_1Damage == true) {
			m_damage1SE = NewGO<SoundSource>(4);
			m_damage1SE->Init(4);
			m_damage1SE->Play(false);
			m_1Damage = false;
			DeleteGO(this);
		}
		break;
	case 1:
		if (m_2Damage == true) {
			m_damage1SE = NewGO<SoundSource>(3);
			m_damage1SE->Init(3);
			m_damage1SE->Play(false);
			m_2Damage = false;
		}
		break;
	case 2:
		if (m_3Damage == true) {
			m_damage1SE = NewGO<SoundSource>(2);
			m_damage1SE->Init(2);
			m_damage1SE->Play(false);
			m_3Damage = false;
		}
		break;
	case 3:
		break;
	}
}