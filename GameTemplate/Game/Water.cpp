#include "stdafx.h"
#include "Water.h"

#include "Game.h"
#include "Player.h"

namespace
{
	const float MAGIC_SIZE = 30.0f;
	const float MAGIC_CIRCLE_SIZE = 50.0f;
}

Water::Water()
{

}

Water::~Water()
{

}

bool Water::Start()
{
	m_player = FindGO<Player>("player");
	
	EffectEngine::GetInstance()->ResistEffect(3, u"Assets/effect/Water.efk");
	m_waterEF = NewGO<EffectEmitter>(3);
	m_waterEF->Init(3);
	m_waterEF->SetPosition(m_position);
	m_waterEF->SetScale(Vector3::One * MAGIC_SIZE);
	m_waterEF->Play();

	EffectEngine::GetInstance()->ResistEffect(8, u"Assets/effect/MagicCircleWater.efk");
	m_waterMagicCircleEF = NewGO<EffectEmitter>(8);
	m_waterMagicCircleEF->Init(8);
	m_waterMagicCircleEF->SetScale(Vector3::One * MAGIC_CIRCLE_SIZE);
	m_waterMagicCircleEF->Play();

	//‰¹º
	g_soundEngine->ResistWaveFileBank(enInitSoundNumber_Water, "Assets/sound/Water.wav");
	m_waterSE = NewGO<SoundSource>(0);
	m_waterSE->Init(enInitSoundNumber_Water);
	m_waterSE->Play(false);

	return true;
}

void Water::Update()
{
	m_position = m_player->GetPosition();
	m_position.y = 10.0f;
	m_waterEF->SetPosition(m_position);

	m_aliveTimer += g_gameTime->GetFrameDeltaTime();

	if (m_aliveTimer < 0.7f) {
		m_magicCirclePosition = m_player->GetPosition();
		m_magicCirclePosition.y = 10.0f;
		m_waterMagicCircleEF->SetPosition(m_magicCirclePosition);
	}
	if (m_aliveTimer > 3.5f) {
		DeleteGO(this);
	}
}