#include "stdafx.h"
#include "Wind.h"

#include "Enemy.h"
#include "Game.h"
#include "Player.h"

namespace
{
	const float MAGIC_SIZE			= 100.0f;
	const float MAGIC_CIRCLE_SIZE	= 50.0f;
}

Wind::Wind()
{

}

Wind::~Wind()
{

}

bool Wind::Start() 
{
	m_player = FindGO<Player>("player");
	m_position = m_player->GetPosition() += g_camera3D->GetForward() * 500.0f;
	m_position.y = 0.0f;

	EffectEngine::GetInstance()->ResistEffect(enInitEffectNumber_Wind, u"Assets/effect/Wind.efk");
	m_windEF = NewGO<EffectEmitter>(0);
	m_windEF->Init(enInitEffectNumber_Wind);
	m_windEF->SetPosition(m_position);
	m_windEF->SetScale(Vector3::One * MAGIC_SIZE);
	m_windEF->Play();
	
	EffectEngine::GetInstance()->ResistEffect(enInitEffectNumber_MagicCircleWind, u"Assets/effect/MagicCircleWind.efk");
	m_windMagicCircleEF = NewGO<EffectEmitter>(0);
	m_windMagicCircleEF->Init(enInitEffectNumber_MagicCircleWind);
	m_windMagicCircleEF->SetScale(Vector3::One * MAGIC_CIRCLE_SIZE);
	m_windMagicCircleEF->Play();

	//‰¹º
	g_soundEngine->ResistWaveFileBank(enInitSoundNumber_Wind, "Assets/sound/Wind.wav");
	m_windSE = NewGO<SoundSource>(0);
	m_windSE->Init(enInitSoundNumber_Wind);
	m_windSE->Play(false);

	return true;
}

void Wind::Update() 
{
	m_aliveTimer += g_gameTime->GetFrameDeltaTime();

	if (m_aliveTimer < 0.7f) 
	{
		m_magicCirclePosition = m_player->GetPosition();
		m_magicCirclePosition.y = 10.0f;
		m_windMagicCircleEF->SetPosition(m_magicCirclePosition);
	}
	if (m_aliveTimer > 3.5f)
	{
		DeleteGO(this);
	}
} 