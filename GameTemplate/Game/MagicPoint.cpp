#include "stdafx.h"
#include "MagicPoint.h"

MagicPoint::MagicPoint() {

}

MagicPoint::~MagicPoint() {

}

bool MagicPoint::Start() {
	EffectEngine::GetInstance()->ResistEffect(11, u"Assets/effect/MagicPoint.efk");
	m_magicPointEF = NewGO<EffectEmitter>(11);
	m_magicPointEF->Init(11);
	m_magicPointEF->SetScale(Vector3::One * 70.0f);
	m_magicPointEF->Play();

	return true;
}

void MagicPoint::Update() {
	m_position.y = 10.0f;
	m_magicPointEF->SetPosition(m_position);

	m_aliveTimer += g_gameTime->GetFrameDeltaTime();

	if (m_aliveTimer > 5.0f) {
		m_magicPointEF->Stop();
		DeleteGO(this);
		m_aliveTimer = 0;
	}
}