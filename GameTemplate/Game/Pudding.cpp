#include "stdafx.h"
#include "Pudding.h"

#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Score.h"

namespace
{
	const float SQUARE_WIDTH = 30.0f;
	const float SQUARE_HEIGHT = 30.0f;
	const float PUDDING_COLLISION_JUDGE = 70.0f;
}

Pudding::Pudding()
{

}

Pudding::~Pudding()
{

}

bool Pudding::Start()
{
	//画像
	m_puddingMap.Init("Assets/sprite/Map/Pudding.DDS", SQUARE_WIDTH, SQUARE_HEIGHT);
	m_puddingMapGray.Init("Assets/sprite/Map/PuddingGray.DDS", SQUARE_WIDTH, SQUARE_HEIGHT);

	//エフェクト
	EffectEngine::GetInstance()->ResistEffect(13, u"Assets/effect/Pudding.efk");
	m_puddingEF = NewGO<EffectEmitter>(13);
	m_puddingEF->Init(13);
	m_puddingEF->SetScale(Vector3::One * 20.0f);
	m_puddingEF->Play();

	//サウンド
	g_soundEngine->ResistWaveFileBank(13, "Assets/sound/PuddingGet.wav");

	m_game = FindGO<Game>("game");
	m_map = FindGO<Map>("map");
	m_player = FindGO<Player>("player");
	m_score = FindGO<Score>("score");

	m_isStart = true;

	return true;
}

void Pudding::Update()
{
	m_position.y = 10.0f;
	m_puddingEF->SetPosition(m_position);

	m_aliveTimer += g_gameTime->GetFrameDeltaTime();
	m_diff = m_player->GetPosition() - m_position;

	if (m_aliveTimer > 5.0f) {
		m_puddingEF->Stop();
		DeleteGO(this);
	}
	if (m_diff.Length() <= PUDDING_COLLISION_JUDGE) {
		//サウンド
		m_puddingGetSE = NewGO<SoundSource>(13);
		m_puddingGetSE->Init(13);
		m_puddingGetSE->Play(false);
		//スコア加算
		m_score->AddTotalScore(5.0f);
		//個数計算
		m_score->AddPuddingScore(1);
		//消去
		m_puddingEF->Stop();
		DeleteGO(this);
	}
	MapMove();
}

void Pudding::MapMove()
{
	if (m_game->GetManageState() == 0)
	{
		m_puddingMap.SetPosition({ m_position.x * -0.15f + m_map->GetMapCenterPosition().x,m_position.z * -0.15f + m_map->GetMapCenterPosition().y,0.0f });
		m_puddingMap.Update();
	}
	m_puddingMapGray.SetPosition({ m_position.x * -0.15f + m_map->GetMapCenterPosition().x,m_position.z * -0.15f + m_map->GetMapCenterPosition().y,0.0f });
	m_puddingMapGray.Update();
}