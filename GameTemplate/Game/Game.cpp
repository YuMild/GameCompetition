#include "stdafx.h"
#include "Game.h"

#include "BackGround.h"
#include "GameCamera.h"
#include "Player.h"

Game::Game() {

}

Game::~Game() {

}

bool Game::Start()
{
	backGround = NewGO<BackGround>(0, "backGround");
	player = NewGO<Player>(0, "player");
	gameCamera = NewGO<GameCamera>(0, "gameCamera");

	return true;
}

void Game::Update()
{
}

void Game::Render(RenderContext& rc)
{
}