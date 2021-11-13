#include "stdafx.h"
#include "Game.h"

#include "BackGround.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "Map.h"
#include "Player.h"

Game::Game() {

}

Game::~Game() {

}

bool Game::Start()
{
	m_backGround = NewGO<BackGround>(0, "backGround");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_map = NewGO<Map>(0, "map");
	m_player = NewGO<Player>(0, "player");
	
	return true;
}

void Game::Update()
{
	if (m_spawnTimer > 2.0f - level)
	{
		NewGO<Enemy>(0, "Enemy");
		m_spawnTimer = 0.0f;
	}
}

void Game::Render(RenderContext& rc)
{
}