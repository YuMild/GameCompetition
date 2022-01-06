#include "stdafx.h"
#include "MagicPoint.h"

#include "Map.h"
#include "Mp.h"
#include "Player.h"

MagicPoint::MagicPoint()
{

}

MagicPoint::~MagicPoint()
{

}

bool MagicPoint::Start()
{
	m_magicPointMap.Init("Assets/sprite/Map/MagicPoint.DDS",30.0f,30.0f);
	m_magicPointMapGray.Init("Assets/sprite/Map/MagicPointGray.DDS", 30.0f, 30.0f);

	EffectEngine::GetInstance()->ResistEffect(11, u"Assets/effect/MagicPoint.efk");
	m_magicPointEF = NewGO<EffectEmitter>(11);
	m_magicPointEF->Init(11);
	m_magicPointEF->SetScale(Vector3::One * 50.0f);
	m_magicPointEF->Play();

	EffectEngine::GetInstance()->ResistEffect(12, u"Assets/effect/MagicPointDelete.efk");

	g_soundEngine->ResistWaveFileBank(12, "Assets/sound/MagicPoint.wav");
	
	m_map = FindGO<Map>("map");
	m_mp = FindGO<Mp>("mp");
	m_player = FindGO<Player>("player");

	m_isStart = true;

	return true;
}

void MagicPoint::Update()
{
	m_position.y = 10.0f;
	m_magicPointEF->SetPosition(m_position);
	
	m_aliveTimer += g_gameTime->GetFrameDeltaTime();
	m_diff = m_player->GetPosition() - m_position;

	if (m_aliveTimer > 5.0f) {
		//エフェクト再生
		m_magicPointDeleteEF = NewGO<EffectEmitter>(12);
		m_magicPointDeleteEF->Init(12);
		m_magicPointDeleteEF->SetScale(Vector3::One * 50.0f);
		m_magicPointDeleteEF->Play();
		m_magicPointDeleteEF->SetPosition(m_position);
		m_magicPointEF->Stop();
		DeleteGO(this);
	}
	if (m_diff.Length() <= 70.0f) {
		//エフェクト再生
		m_magicPointDeleteEF = NewGO<EffectEmitter>(12);
		m_magicPointDeleteEF->Init(12);
		m_magicPointDeleteEF->SetScale(Vector3::One * 50.0f);
		m_magicPointDeleteEF->Play();
		m_magicPointDeleteEF->SetPosition(m_position);
		//音声再生
		m_magicPointSE = NewGO<SoundSource>(12);
		m_magicPointSE->Init(12);
		m_magicPointSE->Play(false);
		m_magicPointEF->Stop();
		//MP加算
		m_mp->AddMp(10.0f);
		DeleteGO(this);
	}
	MapMove();
}

void MagicPoint::MapMove()
{
	m_magicPointMapGray.SetPosition({ m_position.x * -0.15f + m_map->GetMapCenterPosition().x,m_position.z * -0.15f + m_map->GetMapCenterPosition().y,0.0f });
	m_magicPointMapGray.Update();

	m_magicPointMap.SetPosition({ m_position.x * -0.15f + m_map->GetMapCenterPosition().x,m_position.z * -0.15f + m_map->GetMapCenterPosition().y,0.0f });
	m_magicPointMap.Update();
}