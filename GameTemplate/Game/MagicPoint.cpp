#include "stdafx.h"
#include "MagicPoint.h"

#include "Mp.h"
#include "Player.h"

MagicPoint::MagicPoint()
{
}

MagicPoint::~MagicPoint()
{
}

bool MagicPoint::Start()
{
	EffectEngine::GetInstance()->ResistEffect(11, u"Assets/effect/MagicPoint.efk");
	m_magicPointEF = NewGO<EffectEmitter>(11);
	m_magicPointEF->Init(11);
	m_magicPointEF->SetScale(Vector3::One * 50.0f);
	m_magicPointEF->Play();

	EffectEngine::GetInstance()->ResistEffect(12, u"Assets/effect/MagicPointDelete.efk");
	
	m_mp = FindGO<Mp>("mp");
	m_player = FindGO<Player>("player");

	return true;
}

void MagicPoint::Update()
{
	m_position.y = 10.0f;
	m_magicPointEF->SetPosition(m_position);
	
	m_aliveTimer += g_gameTime->GetFrameDeltaTime();

	m_diff = m_player->GetPosition() - m_position;

	if (m_aliveTimer > 5.0f) {
		m_magicPointDeleteEF = NewGO<EffectEmitter>(12);
		m_magicPointDeleteEF->Init(12);
		m_magicPointDeleteEF->SetScale(Vector3::One * 50.0f);
		m_magicPointDeleteEF->Play();
		m_magicPointDeleteEF->SetPosition(m_position);
		m_magicPointEF->Stop();
		DeleteGO(this);
	}
	if (m_diff.Length() <= 70.0f) {
		m_magicPointDeleteEF = NewGO<EffectEmitter>(12);
		m_magicPointDeleteEF->Init(12);
		m_magicPointDeleteEF->SetScale(Vector3::One * 50.0f);
		m_magicPointDeleteEF->Play();
		m_magicPointDeleteEF->SetPosition(m_position);
		m_magicPointEF->Stop();
		m_mp->AddMp(10.0f);
		DeleteGO(this);
	}
}