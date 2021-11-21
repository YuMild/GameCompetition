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
	m_shineSE->SetVolume(0.1f);
	m_shineSE->Play(false);

	//エフェクト
	EffectEngine::GetInstance()->ResistEffect(5, u"Assets/effect/shine.efk");
	m_shineEF = NewGO<EffectEmitter>(5);
	m_shineEF->Init(5);
	m_shineEF->SetPosition(m_position);
	m_shineEF->SetScale(Vector3::One * 10.0f);
	Quaternion quaternion;
	quaternion.SetRotationDegX(90.0f);
	m_shineEF->SetRotation(quaternion);
	m_shineEF->Play();

	return true;
}

void Shine::Update() {
	m_aliveTimer += g_gameTime->GetFrameDeltaTime();
	if (m_aliveTimer > 5.0f) {
		DeleteGO(this);
		m_aliveTimer = 0;
	}
}