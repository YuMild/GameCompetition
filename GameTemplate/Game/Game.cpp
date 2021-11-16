#include "stdafx.h"
#include "Game.h"

#include "BackGround.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "GameOver.h"
#include "Map.h"
#include "Player.h"

#include "nature/SkyCube.h"

Game::Game() {

}

Game::~Game() {
	const auto& enemys = FindGOs<Enemy>("Enemy");//ëSÇƒÇÃÉGÉlÉ~Å[ÇÃçÌèú
	int size = enemys.size();
	for (int i = 0; i < size; i++)
	{
		DeleteGO(enemys[i]);
	}
	DeleteGO(m_backGround);
	DeleteGO(m_gameCamera);
	DeleteGO(m_map);
	DeleteGO(m_player);
	DeleteGO(m_skyCube);
}

bool Game::Start()
{
	m_backGround = NewGO<BackGround>(0, "backGround");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_map = NewGO<Map>(0, "map");
	m_player = NewGO<Player>(0, "player");
	m_skyCube = NewGO<SkyCube>(0, "skyCube");
	
	//îwåi
	m_skyCube->SetScale({ 300.0f, 300.0f, 300.0f });
	m_skyCube->SetType(enSkyCubeType_NightToon);

	return true;
}

void Game::Update()
{
	m_timer += g_gameTime->GetFrameDeltaTime();
	m_spawnTimer += g_gameTime->GetFrameDeltaTime();

	if (m_spawnTimer > 2.0f - m_level)
	{
		NewGO<Enemy>(0, "Enemy");
		m_spawnTimer = 0.0f;
	}

	//ÉåÉxÉã
	if (m_timer > 10.0f)
	{
		if (m_level <= 1.8) {
			m_level += 0.1f;
		}
		m_levelFont += 1;
		m_timer = 0;
	}

	//éÄñSîªíË//
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
	//óéâ∫éÄñS//
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