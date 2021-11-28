#include "stdafx.h"
#include "Shine.h"

#include "Enemy.h"
#include "Player.h"
#include "graphics/effect/EffectEmitter.h"

Shine::Shine() {

}
Shine::~Shine() {

}
bool Shine::Start() {

	m_player = FindGO<Player>("player");
	m_position.y = 10.0f;

	//音声
	g_soundEngine->ResistWaveFileBank(7, "Assets/sound/Shine.wav");
	m_shineSE = NewGO<SoundSource>(7);
	m_shineSE->Init(7);
	m_shineSE->Play(false);

	//エフェクト
	EffectEngine::GetInstance()->ResistEffect(5, u"Assets/effect/shine.efk");
	m_shineEF = NewGO<EffectEmitter>(5);
	m_shineEF->Init(5);
	m_shineEF->SetPosition(m_position);
	m_shineEF->SetScale(Vector3::One * 10.0f);

	EffectEngine::GetInstance()->ResistEffect(10, u"Assets/effect/MagicCircleShine.efk");
	m_shineMagicCircleEF = NewGO<EffectEmitter>(10);
	m_shineMagicCircleEF->Init(10);
	m_shineMagicCircleEF->SetScale(Vector3::One * 50.0f);
	m_shineMagicCircleEF->Play();

	Quaternion quaternion;
	quaternion.SetRotationDegX(90.0f);
	m_shineEF->SetRotation(quaternion);
	m_shineEF->Play();

	m_isMoving == true;

	g_renderingEngine->SetIsGrayScale(true);

	return true;
}

void Shine::Update() {

	m_aliveTimer += g_gameTime->GetFrameDeltaTime();

	if (m_aliveTimer < 0.7f) {
		m_magicCirclePosition = m_player->GetPosition();
		m_magicCirclePosition.y = 10.0f;
		m_shineMagicCircleEF->SetPosition(m_magicCirclePosition);
	}
	if (m_aliveTimer > 5.3f) {
		DeleteGO(this);
		g_renderingEngine->SetIsGrayScale(false);
	}
}