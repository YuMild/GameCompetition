#include "stdafx.h"
#include "Game.h"

#include "BackGround.h"
#include "GameCamera.h"
#include "Map.h"
#include "Player.h"

Game::Game() {

}

Game::~Game() {

}

bool Game::Start()
{
	
	backGround = NewGO<BackGround>(0, "backGround");
	gameCamera = NewGO<GameCamera>(0, "gameCamera");
	map = NewGO<Map>(0, "map");
	player = NewGO<Player>(0, "player");
	
	return true;
}

void Game::Update()
{
}

void Game::Render(RenderContext& rc)
{
}