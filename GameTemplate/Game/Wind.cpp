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
	m_position = m_player->GetPosition() += g_camera3D->GetForward() * 200.0f;
	m_position.y = 0.0f;

	EffectEngine::GetInstance()->ResistEffect(3, u"Assets/effect/tornado.efk");

	m_windEF = NewGO<EffectEmitter>(3);
	m_windEF->Init(3);
	m_windEF->SetPosition(m_position);
	m_windEF->SetScale(Vector3::One * 50.0f);
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