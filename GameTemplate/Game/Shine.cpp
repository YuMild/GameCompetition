#include "stdafx.h"
#include "Shine.h"

#include "Enemy.h"
#include "Game.h"
#include "Player.h"
#include "graphics/effect/EffectEmitter.h"

namespace
{
	const float MAGIC_SIZE = 10.0f;
	const float MAGIC_CIRCLE_SIZE = 50.0f;
}

Shine::Shine()
{

}

Shine::~Shine() 
{

}

bool Shine::Start() 
{

	m_player = FindGO<Player>("player");
	m_position.y = 10.0f;

	//音声
	g_soundEngine->ResistWaveFileBank(enInitSoundNumber_Shine, "Assets/sound/Shine.wav");
	m_shineSE = NewGO<SoundSource>(0);
	m_shineSE->Init(enInitSoundNumber_Shine);
	m_shineSE->Play(false);

	//エフェクト
	EffectEngine::GetInstance()->ResistEffect(enInitEffectNumber_Shine, u"Assets/effect/shine.efk");
	m_shineEF = NewGO<EffectEmitter>(0);
	m_shineEF->Init(enInitEffectNumber_Shine);
	m_shineEF->SetPosition(m_position);
	m_shineEF->SetScale(Vector3::One * MAGIC_SIZE);

	EffectEngine::GetInstance()->ResistEffect(enInitEffectNumber_MagicCircleShine, u"Assets/effect/MagicCircleShine.efk");
	m_shineMagicCircleEF = NewGO<EffectEmitter>(0);
	m_shineMagicCircleEF->Init(enInitEffectNumber_MagicCircleShine);
	m_shineMagicCircleEF->SetScale(Vector3::One * MAGIC_CIRCLE_SIZE);
	m_shineMagicCircleEF->Play();

	Quaternion quaternion;
	quaternion.SetRotationDegX(90.0f);
	m_shineEF->SetRotation(quaternion);
	m_shineEF->Play();

	m_isMoving == true;

	g_renderingEngine->SetIsGrayScale(true);

	return true;
}

void Shine::Update() 
{
	m_aliveTimer += g_gameTime->GetFrameDeltaTime();

	if (m_aliveTimer < 0.7f) 
	{
		m_magicCirclePosition = m_player->GetPosition();
		m_magicCirclePosition.y = 10.0f;
		m_shineMagicCircleEF->SetPosition(m_magicCirclePosition);
	}
	if (m_aliveTimer > 5.3f) 
	{
		DeleteGO(this);
		g_renderingEngine->SetIsGrayScale(false);
	}
}