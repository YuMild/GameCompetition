#include "stdafx.h"
#include "Game.h"
#include "BackGround.h"
#include "Bullet.h"
#include "Enemy.h"
#include "GameCamera.h"
#include "GameOver.h"
#include "Player.h"
#include "sound/SoundEngine.h"

bool Game::Start()
{
	//NewGO
	m_player = NewGO<Player>(0, "player");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_backGround = NewGO<BackGround>(0, "backGround");

	//フレーム
	frameRender.Init("Assets/sprite/frame.dds", 100.0f, 100.0f);
	frameposition.x = -400.0f;
	frameposition.y = 200.0f;

	//HP
	hpgreenRender.Init("Assets/sprite/HPgreen.dds", 200.0f, 200.0f);
	hpgreenRender.SetPosition({ -285.0f,-300.0f,0.0f });
	hpdeathgreenRender.Init("Assets/sprite/HPdeathgreen.dds", 200.0f, 200.0f);
	hpdeathgreenRender.SetPosition({ -285.0f,-300.0f,0.0f });
	hpyellowRender.Init("Assets/sprite/HPyellow.dds", 200.0f, 200.0f);
	hpyellowRender.SetPosition({ -400.0f,-300.0f,0.0f });
	hpdeathyellowRender.Init("Assets/sprite/HPdeathyellow.dds", 200.0f, 200.0f);
	hpdeathyellowRender.SetPosition({ -400.0f,-300.0f,0.0f });
	hpredRender.Init("Assets/sprite/HPred.dds", 200.0f, 200.0f);
	hpredRender.SetPosition({ -515.0f,-300.0f,0.0f });
	hpdeathredRender.Init("Assets/sprite/HPdeathred.dds", 200.0f, 200.0f);
	hpdeathredRender.SetPosition({ -515.0f,-300.0f,0.0f });
	hpgreenRender.Update();
	hpdeathgreenRender.Update();
	hpyellowRender.Update();
	hpdeathyellowRender.Update();
	hpredRender.Update();
	hpdeathredRender.Update();

	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/damage1.wav");
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/damage2.wav");
	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/damage3.wav");

	return true;
}

Game::Game() {

}

Game::~Game() {
	const auto& enemys = FindGOs<Enemy>("Enemy");
	int size = enemys.size();
	for (int i = 0; i < size; i++)
	{
		DeleteGO(enemys[i]);
	}
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	DeleteGO(m_backGround);
}

void Game::Update()
{

	wchar_t text[255];
	swprintf_s(text, 255, L"レベル%d", levelfont);

	//表示するテキストを設定。
	limitFont.SetText(text);
	//フォントの位置を設定。
	limitFont.SetPosition(Vector3(300.0f, 300.0f, 0.0f));
	//フォントの大きさを設定。
	limitFont.SetScale(1.0f);

	timer += g_gameTime->GetFrameDeltaTime();
	spawntimer += g_gameTime->GetFrameDeltaTime();

	//スポーン間隔

	if (spawntimer > 2.0f - level)
	{
		NewGO<Enemy>(0, "Enemy");
		spawntimer = 0.0f;
	}

	//レベル
	if (timer > 10.0f)
	{
		if (level <= 1.8) {
			level += 0.1f;
		}
		levelfont += 1;
		timer = 0;
	}

	//死亡判定//
	const auto& enemyList = FindGOs<Enemy>("Enemy");
	for (auto enemy : enemyList)
	{
		Vector3 unitydiff = m_player->playerPosition - enemy->enemyposition;
		if (unitydiff.Length() <= 10.0f) {
			if (hp >= 1) {
				hp -= 1;
				DeleteGO(enemy);

			}
			if (hp == 0) {
				NewGO<GameOver>(0, "GameOver");
			}
		}
	}

	//落下死亡//
	if (m_player->playerPosition.y <= -100.0f)
	{
		NewGO<GameOver>(0, "GameOver");
		DeleteGO(this);
	}
}

void Game::Render(RenderContext& rc)
{
	//モデル
	m_modelRender.Draw(rc);

	switch (hp) {
	case 0:
		if (hp0 == true) {
			damage1SE = NewGO<SoundSource>(4);
			damage1SE->Init(4);
			damage1SE->Play(false);
			hp0 = false;
			DeleteGO(this);
		}
		break;
	case 1:
		hpdeathgreenRender.Draw(rc);
		hpdeathyellowRender.Draw(rc);
		hpredRender.Draw(rc);
		if (hp1 == true) {
			damage1SE = NewGO<SoundSource>(3);
			damage1SE->Init(3);
			damage1SE->Play(false);
			hp1 = false;
		}
		break;
	case 2:
		hpdeathgreenRender.Draw(rc);
		hpyellowRender.Draw(rc);
		hpredRender.Draw(rc);
		if (hp2 == true) {
			damage1SE = NewGO<SoundSource>(2);
			damage1SE->Init(2);
			damage1SE->Play(false);
			hp2 = false;
		}
		break;
	case 3:
		hpgreenRender.Draw(rc);
		hpyellowRender.Draw(rc);
		hpredRender.Draw(rc);
		break;
	}

	//画像
	frameRender.Draw(rc);

	//フォント
	limitFont.Draw(rc);
	levelFont.Draw(rc);
}