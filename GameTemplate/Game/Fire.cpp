#include "stdafx.h"
#include "Fire.h"

#include "Player.h"

namespace
{
	const float MAGIC_SIZE = 50.0f;
	const float MAGIC_CIRCLE_SIZE = 50.0f;
}

Fire::Fire() {

}

Fire::~Fire() {

}

bool Fire::Start() {

	m_player = FindGO<Player>("player");
	
	EffectEngine::GetInstance()->ResistEffect(2,u"Assets/effect/Fire.efk");
	m_fireEF = NewGO<EffectEmitter>(2);
	m_fireEF->Init(2);
	m_fireEF->SetScale(Vector3::One * MAGIC_SIZE);
	m_fireEF->Play();

	EffectEngine::GetInstance()->ResistEffect(7, u"Assets/effect/MagicCircleFire.efk");
	m_fireMagicCircleEF = NewGO<EffectEmitter>(7); 
	m_fireMagicCircleEF->Init(7);
	m_fireMagicCircleEF->SetScale(Vector3::One * MAGIC_CIRCLE_SIZE);
	m_fireMagicCircleEF->Play();

	//????
	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/Fire.wav");
	m_fireSE = NewGO<SoundSource>(4);
	m_fireSE->Init(4);
	m_fireSE->Play(false);

	return true;
}

void Fire::Update()
{
	m_aliveTimer += g_gameTime->GetFrameDeltaTime();

	if (m_aliveTimer <= 0.7f) {//???@?w
		m_magicCirclePosition = m_player->GetPosition();
		m_magicCirclePosition.y = 10.0f;
		m_fireMagicCircleEF->SetPosition(m_magicCirclePosition);
	}
	if (m_aliveTimer <= 5.0f) {//?ǔ?
		m_position = m_player->GetPosition();
		m_position.y = 10.0f;
		m_fireEF->SetPosition(m_position);
	}
	if (m_aliveTimer >= 2.3f) {//?????蔻??
		m_isMoving = true;
	}
	if (m_aliveTimer >= 3.0f) {//????
		DeleteGO(this);
	}
}

