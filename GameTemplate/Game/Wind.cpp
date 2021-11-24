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

	EffectEngine::GetInstance()->ResistEffect(4, u"Assets/effect/Wind.efk");
	
	m_windEF = NewGO<EffectEmitter>(4);
	m_windEF->Init(4);
	m_windEF->SetPosition(m_position);
	m_windEF->SetScale(Vector3::One * 100.0f);
	m_windEF->Play();
	
	EffectEngine::GetInstance()->ResistEffect(9, u"Assets/effect/MagicCircleWind.efk");
	m_windMagicCircleEF = NewGO<EffectEmitter>(9);
	m_windMagicCircleEF->Init(9);
	m_windMagicCircleEF->SetScale(Vector3::One * 50.0f);
	m_windMagicCircleEF->Play();

	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/Wind.wav");

	m_windSE = NewGO<SoundSource>(6);
	m_windSE->Init(6);
	m_windSE->Play(false);

	return true;
}

void Wind::Update() {
	
	m_aliveTimer += g_gameTime->GetFrameDeltaTime();

	if (m_aliveTimer < 0.8f) {
		m_magicCirclePosition = m_player->GetPosition();
		m_magicCirclePosition.y = 10.0f;
		m_windMagicCircleEF->SetPosition(m_magicCirclePosition);
	}
	if (m_aliveTimer > 3.5f) {
		DeleteGO(this);
		m_aliveTimer = 0;
	}
} 