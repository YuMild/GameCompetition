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
	g_soundEngine->ResistWaveFileBank(8, "Assets/sound/Shine.wav");
	m_shineSE = NewGO<SoundSource>(8);
	m_shineSE->Init(8);
	m_shineSE->Play(false);

	//g_soundEngine->ResistWaveFileBank(9, "Assets/sound/shine2.wav");
	//m_shineSE_2 = NewGO<SoundSource>(9);
	//m_shineSE_2->Init(9);
	//m_shineSE_2->Play(false);

	//エフェクト
	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/effect/shine.efk");
	m_shineEF = NewGO<EffectEmitter>(1);
	m_shineEF->Init(1);
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