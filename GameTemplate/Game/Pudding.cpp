#include "stdafx.h"
#include "Pudding.h"

#include "Map.h"
#include "Player.h"
#include "Score.h"

Pudding::Pudding()
{

}

Pudding::~Pudding()
{

}

bool Pudding::Start()
{
	//画像
	m_puddingMap.Init("Assets/sprite/Pudding.DDS", 30.0f, 30.0f);

	//エフェクト
	EffectEngine::GetInstance()->ResistEffect(13, u"Assets/effect/Pudding.efk");
	m_puddingEF = NewGO<EffectEmitter>(13);
	m_puddingEF->Init(13);
	m_puddingEF->SetScale(Vector3::One * 20.0f);
	m_puddingEF->Play();

	//サウンド
	g_soundEngine->ResistWaveFileBank(13, "Assets/sound/PuddingGet.wav");

	m_map = FindGO<Map>("map");
	m_player = FindGO<Player>("player");
	m_score = FindGO<Score>("score");

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
	if (m_diff.Length() <= 70.0f) {
		m_puddingGetSE = NewGO<SoundSource>(13);
		m_puddingGetSE->Init(13);
		m_puddingGetSE->Play(false);
		m_score->AddScore(5.0f);
		m_puddingEF->Stop();
		DeleteGO(this);
	}
	MapMove();
}

void Pudding::MapMove()
{
	m_puddingMap.SetPosition({ m_position.x * -0.15f + m_map->GetMapCenterPosition().x,m_position.z * -0.15f + m_map->GetMapCenterPosition().y,0.0f });
	m_puddingMap.Update();
}