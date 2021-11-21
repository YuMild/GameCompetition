#include "stdafx.h"
#include "Wind.h"

#include "Enemy.h"
#include "Player.h"
#include "graphics/effect/EffectEmitter.h"

Wind::Wind() {

}

Wind::~Wind() {

}

bool Wind::Start() {
	m_player = FindGO<Player>("player");
	m_position = m_player->GetPosition() += g_camera3D->GetForward() * 500.0f;
	m_position.y = 0.0f;

	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/Wind.wav");

	m_windSE = NewGO<SoundSource>(6);
	m_windSE->Init(6);
	m_windSE->SetVolume(0.1f);
	m_windSE->Play(false);

	EffectEngine::GetInstance()->ResistEffect(4, u"Assets/effect/Wind.efk");

	m_windEF = NewGO<EffectEmitter>(4);
	m_windEF->Init(4);
	m_windEF->SetPosition(m_position);
	m_windEF->SetScale(Vector3::One * 70.0f);
	m_windEF->Play();
	return true;
}

void Wind::Update() {
	m_aliveTimer += g_gameTime->GetFrameDeltaTime();
	if (m_aliveTimer > 3.5f) {
		DeleteGO(this);
		m_aliveTimer = 0;
	}
} 