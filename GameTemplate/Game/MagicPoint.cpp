#include "stdafx.h"
#include "MagicPoint.h"

#include "Game.h"
#include "Map.h"
#include "Mp.h"
#include "Player.h"

namespace
{
	const float EFFECT_SIZE = 50.0f;
	const float EFFECT_MAP_SIZE = 0.15f;
	const float COLLISION_SIZE = 70.0f;
	const float ADD_MP = 15.0f;
	const float SQUARE_WIDTH = 30.0f;
	const float SQUARE_HEIGHT = 30.0f;
}

MagicPoint::MagicPoint()
{

}

MagicPoint::~MagicPoint()
{

}

bool MagicPoint::Start()
{
	m_magicPointMap.Init("Assets/sprite/Map/MagicPoint.DDS", SQUARE_WIDTH, SQUARE_HEIGHT);
	m_magicPointMapGray.Init("Assets/sprite/Map/MagicPointGray.DDS", SQUARE_WIDTH, SQUARE_HEIGHT);

	EffectEngine::GetInstance()->ResistEffect(enInitEffectNumber_MagicPoint, u"Assets/effect/MagicPoint.efk");
	m_magicPointEF = NewGO<EffectEmitter>(0);
	m_magicPointEF->Init(enInitEffectNumber_MagicPoint);
	m_magicPointEF->SetScale(Vector3::One * EFFECT_SIZE);
	m_magicPointEF->Play();

	EffectEngine::GetInstance()->ResistEffect(enInitEffectNumber_MagicPointDelete, u"Assets/effect/MagicPointDelete.efk");

	g_soundEngine->ResistWaveFileBank(enInitSoundNumber_MagicPoint, "Assets/sound/MagicPoint.wav");
	
	m_map = FindGO<Map>("map");
	m_mp = FindGO<Mp>("mp");
	m_player = FindGO<Player>("player");

	m_isStart = true;

	return true;
}

void MagicPoint::Update()
{
	MapMove();

	m_position.y = 10.0f;
	m_magicPointEF->SetPosition(m_position);
	
	m_aliveTimer += g_gameTime->GetFrameDeltaTime();
	m_diff = m_player->GetPosition() - m_position;

	if (m_aliveTimer > 5.0f)
	{
		//エフェクト再生
		PlayMagicPointDeleteEffect();
		m_magicPointEF->Stop();
		DeleteGO(this);
	}
	if (m_diff.Length() <= COLLISION_SIZE)
	{
		//エフェクト再生
		PlayMagicPointDeleteEffect();
		m_magicPointEF->Stop();
		//音声再生
		m_magicPointSE = NewGO<SoundSource>(0);
		m_magicPointSE->Init(enInitSoundNumber_MagicPoint);
		m_magicPointSE->Play(false);
		//MP加算
		m_mp->AddMp(ADD_MP);
		DeleteGO(this);
	}
}

void MagicPoint::MapMove()
{
	m_magicPointMapGray.SetPosition({ m_position.x * -EFFECT_MAP_SIZE + m_map->GetMapCenterPosition().x,m_position.z * -EFFECT_MAP_SIZE + m_map->GetMapCenterPosition().y,0.0f });
	m_magicPointMapGray.Update();

	m_magicPointMap.SetPosition({ m_position.x * -EFFECT_MAP_SIZE + m_map->GetMapCenterPosition().x,m_position.z * -EFFECT_MAP_SIZE + m_map->GetMapCenterPosition().y,0.0f });
	m_magicPointMap.Update();
}

void MagicPoint::PlayMagicPointDeleteEffect()
{
	m_magicPointDeleteEF = NewGO<EffectEmitter>(0);
	m_magicPointDeleteEF->Init(enInitEffectNumber_MagicPointDelete);
	m_magicPointDeleteEF->SetScale(Vector3::One * EFFECT_SIZE);
	m_magicPointDeleteEF->Play();
	m_magicPointDeleteEF->SetPosition(m_position);
}