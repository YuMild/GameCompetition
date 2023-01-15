#include "stdafx.h"
#include "Bullet.h"
#include "player.h"
#include "Game.h"
#include "Background.h"
#include "sound/SoundEngine.h"
#include "graphics/effect/EffectEmitter.h"

namespace
{
	const float EFFECT_SIZE = 20.0f;
	const float BULLET_SPEED = 20.0f;
	const float BULLET_SIZE = 0.5f;
}

Bullet::Bullet() 
{

}

Bullet:: ~Bullet() 
{
	DeleteGO(m_gunShotSE);
}

bool Bullet::Start() {

	m_player = FindGO<Player>("player");
	m_render.Init("Assets/modelData/bullet.tkm");
	m_render.SetScale(Vector3::One * BULLET_SIZE);
	m_position = m_player->GetPosition();												//	プレイヤーの場所に生成される
	m_position.y += 50.0f;																//	プレイヤーの上に生成される

	//方向
	m_forward = g_camera3D->GetForward();
	m_forward.y = 0.0f;
	m_forward.Normalize();

	//エフェクト
	EffectEngine::GetInstance()->ResistEffect(enInitEffectNumber_Bullet, u"Assets/effect/Bullet.efk");

	m_fireBallEF = NewGO<EffectEmitter>(0);
	m_fireBallEF->Init(enInitEffectNumber_Bullet);
	m_fireBallEF->SetScale(Vector3::One * EFFECT_SIZE);
	m_fireBallEF->Play();

	//音声ファイル
	g_soundEngine->ResistWaveFileBank(enInitSoundNumber_Bullet, "Assets/sound/Bullet.wav");

	//音声
	m_gunShotSE = NewGO<SoundSource>(0);
	m_gunShotSE->Init(enInitSoundNumber_Bullet);
	m_gunShotSE->Play(false);

	m_moveSpeed = m_forward * BULLET_SPEED;													//	移動速度

	return true;
}

void Bullet::Update() 
{
	Move();
	m_fireBallEF->SetPosition(m_position);

	m_deleteTimer += g_gameTime->GetFrameDeltaTime();

	//タイマーが2.0以上の時
	if (m_deleteTimer >= 2.0f)
	{
		DeleteGO(this);																	//	自身を削除
	}
}

void Bullet::Render(RenderContext& rc)
{
	m_render.Draw(rc);
}

void Bullet::Move()
{
	m_position += m_moveSpeed;
	m_render.SetPosition(m_position);
	m_render.Update();
}