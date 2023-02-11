#include "stdafx.h"
#include "Game.h"
#include "BackGround.h"
#include "Bullet.h"
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

namespace
{
	const float SKYCUBE_SIZE				= 300.0f;													//	スカイキューブのサイズ
	const float BGM_VOLUME					= 0.5f;														//　BGMの音量
	const float FALL_LINE					= -100.0f;													//　落下死の判定ライン
	const float LEVELUP_TIME				= 12.0f;													//　レベルアップの間隔
	const float ENEMY_SPAWNTIME				= 1.8f;														//　エネミーのスポーン間隔
	const float PUDDING_SPAWNTIME			= 12.0f;													//　プリンのスポーン間隔
	const float MAGICPOINT_SPAWNTIME		= 12.0f;													//　MagicPointのスポーン間隔
	const Vector3 DIRECTIONLIGHT_DIRECTION	= { 0.5f, -0.5f, 0.5f };									//　ライトの射出方向
	const Vector3 DIRECTIONLIGHT_COLOR		= { 2.5f,2.5f,2.5f };										//　ライトの色
}

Game::Game()
{

}

Game::~Game()
{
    g_renderingEngine->SetIsAllGrayScale(false);														//	グレースケールをOFFに
	g_k2Engine->GetK2EngineLow()->SetFrameRateMode(K2EngineLow::enFrameRateMode_Variable, 60.0f);		//	FPSを元に戻す

	//	DeleteGO
	DeleteGO(m_backGround);																				//	BackGround
	DeleteGO(m_backGroundBGM);																			//	BGM
	const auto& bullets = FindGOs<Bullet>("bullet");													//	Bullet
	for (auto& Bullet : bullets)
	{
		DeleteGO(Bullet);
	}
	DeleteGO(m_clock);																					//	Clock
	const auto& enemys = FindGOs<Enemy>("enemy");														//	Enemy
	for (auto& Enemy : enemys)
	{
		DeleteGO(Enemy);
	}
	DeleteGO(m_gameCamera);																				//	GameCamera
	DeleteGO(m_hp);																						//	HP
	DeleteGO(m_magic);																					//	Magic
	const auto& magicPoints = FindGOs<MagicPoint>("magicPoint");										//	MagicPoint
	for (auto& MagicPoint : magicPoints)
	{
		DeleteGO(MagicPoint);
	}
	DeleteGO(m_map);																					//	Map
	DeleteGO(m_mp);																						//	MP
	DeleteGO(m_player);																					//	Player
	DeleteGO(m_pudding);																				//	Pudding
	DeleteGO(m_score);																					//	Score
	DeleteGO(m_skyCube);																				//	SkyCube
}

bool Game::Start()
{
	//	NewGO
	m_backGround	= NewGO<BackGround>(0, "backGround");												//	BackGround
	m_clock			= NewGO<Clock>(0, "clock");															//	Clock
	m_gameCamera	= NewGO<GameCamera>(0, "gameCamera");												//	GameCamera
	m_hp			= NewGO<Hp>(0, "hp");																//	HP
	m_magic			= NewGO<Magic>(0, "magic");															//	Magic
	m_map			= NewGO<Map>(0, "map");																//	Map
	m_mp			= NewGO<Mp>(0, "mp");																//	MP
	m_player		= NewGO<Player>(0, "player");														//	Player
	m_score			= NewGO<Score>(0, "score");															//	Score
	m_skyCube		= NewGO<SkyCube>(0, "skyCube");														//	SkyCube

	//	背景
	m_skyCube->SetScale(Vector3::One * 300.0f);															//	サイズ
	m_skyCube->SetType(enSkyCubeType_NightToon);														//	SkyCubeの種類
	m_skyCube->SetLuminance(0.5);																		//	輝度

	//	音声
	g_soundEngine->ResistWaveFileBank(enInitSoundNumber_BackGround, "Assets/sound/BackGround.wav");		//	BGM
	m_backGroundBGM = NewGO<SoundSource>(0);
	m_backGroundBGM->Init(enInitSoundNumber_BackGround);
	m_backGroundBGM->SetVolume(BGM_VOLUME);
	m_backGroundBGM->Play(true);

	// ライト
	g_sceneLight->SetDirectionLight(0, DIRECTIONLIGHT_DIRECTION, DIRECTIONLIGHT_COLOR);					//	ディレクションライト
	
	return true;
}

void Game::Update()
{
	Fall();
	ManageState();
	if (m_hp->GetHP() == 0)																				//	プレイヤーのHPが0の時
	{
		return;																							//	関数の処理を終了させる
	}
	EnemyGenerate();
	MagicPointGenerate();
	PuddingGenerate();
	Timer();
}

void Game::Fall()
{
	//　ステージ外に落下したらHPを0にする
	if (m_player->GetPosition().y <= FALL_LINE)
	{
		m_hp->SetHP(0);
	}
}

void Game::Timer() 
{
	m_timer += g_gameTime->GetFrameDeltaTime();
	m_enemySpawnTimer += g_gameTime->GetFrameDeltaTime();
	m_magicPointSpawnTimer += g_gameTime->GetFrameDeltaTime();
	m_puddingSpawnTimer += g_gameTime->GetFrameDeltaTime();

	//	レベルアップ
	if (m_timer > LEVELUP_TIME)
	{
		//　レベルを上げる(上限は15)
		if (m_level < 15) {
			m_level += 1;
		}
		m_timer = 0.0f;
	}
}

void Game::EnemyGenerate()
{
	if (m_enemySpawnTimer > ENEMY_SPAWNTIME - m_level / 10)
	{
		constexpr int MIN = -500;																		//	乱数の範囲最低値
		constexpr int MAX = 500;																		//	乱数の範囲最大値

		Vector3 position;
		random_device rd;
		default_random_engine eng(rd());
		uniform_int_distribution<int> distr(MIN, MAX);

		position.x = distr(eng);
		position.z = distr(eng);
		position.y = 0.0f;

		m_enemy = NewGO<Enemy>(0, "enemy");
		m_enemy->SetPosition(position);
		m_enemySpawnTimer = 0.0f;
	}
}

void Game::MagicPointGenerate()
{
	if (m_magicPointSpawnTimer > MAGICPOINT_SPAWNTIME)
	{
		constexpr int MIN = -500;																		//	乱数の範囲最低値
		constexpr int MAX = 500;																		//	乱数の範囲最大値

		Vector3 position;
		random_device rd;
		default_random_engine eng(rd());
		uniform_int_distribution<int> distr(MIN, MAX);													//	MINとMAXの間でランダムな値を作成

		position.x = distr(eng);
		position.z = distr(eng);
		position.y = 0.0f;

		m_magicPoint = NewGO<MagicPoint>(0, "magicPoint");
		m_magicPoint->SetPosition(position);
		m_magicPointSpawnTimer = 0.0f;																	//	タイマーのリセット
	}
}

void Game::PuddingGenerate()
{
	if (m_puddingSpawnTimer > PUDDING_SPAWNTIME)
	{
		constexpr int MIN = -500;																		//	乱数の範囲最低値
		constexpr int MAX = 500;																		//	乱数の範囲最大値

		Vector3 position;
		random_device rd;
		default_random_engine eng(rd());
		uniform_int_distribution<int> distr(MIN, MAX);													//	MINとMAXの間でランダムな値を作成

		position.x = distr(eng);
		position.z = distr(eng);
		position.y = 0.0f;

		m_pudding = NewGO<Pudding>(0, "pudding");
		m_pudding->SetPosition(position);
		m_puddingSpawnTimer = 0.0f;																		//　タイマーのリセット
	}
}

void Game::ManageState()
{
	//	死亡時
	if (m_gameState != enGameState_PlayerAlive)
	{
		m_stateTimer += g_gameTime->GetFrameDeltaTime();												//	時間経過
	}

	switch (m_gameState)
	{

	//	生存時
	case enGameState_PlayerAlive:

		if (m_hp->GetHP() == 0)																			//	HPが0になるかプレイヤーがステージ外に落下した時
		{
			m_player->SetState(3);																		//	プレイヤーの死亡アニメーションを再生させる
			m_gameState = enGameState_Slow;																//	スローに移行
			m_backGroundBGM->Stop();																	//	BGMをストップさせる
		}
		break;

	//	スロー時
	case enGameState_Slow:

		g_renderingEngine->SetIsAllGrayScale(true);														//	モノクロ
		g_k2Engine->GetK2EngineLow()->SetFrameRateMode(K2EngineLow::enFrameRateMode_Variable, 20.0f);	//	FPSを下げる
		if (m_stateTimer >= 2.0f)																		//	フィニッシュまでのカウントアップ
		{
			m_gameState = enGameState_GameFinish;														//	フィニッシュに移行
			m_stateTimer = 0.0f;																		//	タイマーのリセット
		}
		break;

	//	フィニッシュ時
	case enGameState_GameFinish:

		if (m_stateTimer >= 1.5f)																		//	リザルトまでのカウントアップ
		{
			m_gameState = enGameState_Result;															//	リザルトに移行
			m_stateTimer = 0.0f;																		//	タイマーのリセット
		}
		break;

	//	リザルト時
	case enGameState_Result:

		if (m_isStart == true)																			//	一度だけ実行
		{
			m_result = NewGO<Result>(0, "result");
			m_isStart = false;
		}
		if (m_stateTimer >= 1.0f)
		{
			m_gameState = enGameState_TimeScore;														//	タイムスコアに移行
			m_stateTimer = 0.0f;																		//	タイマーのリセット
		}
		break;

	//	タイムスコア表示
	case enGameState_TimeScore:

		if (m_stateTimer >= 0.8f)
		{
			m_gameState = enGameState_PuddingScore;														//	プリンスコアに移行
			m_stateTimer = 0.0f;																		//	タイマーのリセット
		}
		break;

	//	プリンスコア表示
	case enGameState_PuddingScore:

		if (m_stateTimer >= 0.8f)
		{
			m_gameState = enGameState_TotalScore;														//	トータルスコアに移行
			m_stateTimer = 0.0f;																		//	タイマーのリセット
		}
		break;

	//	トータルスコア表示
	case enGameState_TotalScore:
		if (m_stateTimer >= 1.5f)
		{
			//	Dランク
			if (m_score->GetTotalScoreOld() < 5000.0f)
			{
				m_gameState = enGameState_RankD;
				m_stateTimer = 0.0f;																	//	タイマーのリセット
			}
			//	Cランク
			else if (m_score->GetTotalScoreOld() > 5001.0f && m_score->GetTotalScoreOld() < 10000.0f)
			{
				m_gameState = enGameState_RankC;
				m_stateTimer = 0.0f;																	//	タイマーのリセット
			}
			//	Bランク
			else if (m_score->GetTotalScoreOld() > 10001.0f && m_score->GetTotalScoreOld() < 15000.0f)
			{
				m_gameState = enGameState_RankB;
				m_stateTimer = 0.0f;																	//	タイマーのリセット
			}
			//	Aランク
			else if (m_score->GetTotalScoreOld() > 15001.0f && m_score->GetTotalScoreOld() < 20000.0f)
			{
				m_gameState = enGameState_RankA;
				m_stateTimer = 0.0f;																	//	タイマーのリセット
			}
			//	Sランク
			else if (m_score->GetTotalScoreOld() > 20001.0f)
			{
				m_gameState = enGameState_RankS;
				m_stateTimer = 0.0f;																	//	タイマーのリセット
			}
		}
			
		break;
	}
}