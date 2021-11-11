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
	gameCamera = NewGO<GameCamera>(0, "gameCamera");
	player = NewGO<Player>(0, "player");

	modelRender.Init("Assets/modelData/unityChan.tkm");
	return true;
}

void Game::Update()
{
	modelRender.Update();
}

void Game::Render(RenderContext& rc)
{
	modelRender.Draw(rc);
}