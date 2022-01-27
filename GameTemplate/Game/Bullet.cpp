#include "stdafx.h"
#include "Bullet.h"
#include "player.h"
#include "Game.h"
#include "Background.h"
#include "sound/SoundEngine.h"
#include "graphics/effect/EffectEmitter.h"

Bullet::Bullet() {
}
Bullet:: ~Bullet() {
}
bool Bullet::Start() {

	m_player = FindGO<Player>("player");
	m_render.Init("Assets/modelData/bullet.tkm");
	m_render.SetScale({ 0.5f,0.5f,0.5f });
	m_position = m_player->GetPosition();												//	プレイヤーの場所に生成される
	m_position.y += 50.0f;																//	プレイヤーの上に生成される

	//方向
	m_forward = g_camera3D->GetForward();
	m_forward.y = 0.0f;
	m_forward.Normalize();

	//エフェクト
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/Bullet.efk");

	m_fireBallEF = NewGO<EffectEmitter>(0);
	m_fireBallEF->Init(0);
	m_fireBallEF->SetScale(Vector3::One * 20.0f);
	m_fireBallEF->Play();

	//音声ファイル
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/Bullet.wav");

	//音声
	m_gunShotSE = NewGO<SoundSource>(2);
	m_gunShotSE->Init(2);
	m_gunShotSE->Play(false);

	m_moveSpeed = m_forward * 20.0f;													//	移動速度

	return true;
}

void Bullet::Update() {

	m_deleteTimer += g_gameTime->GetFrameDeltaTime();

	m_fireBallEF->SetPosition(m_position);

	Move();

	//タイマーが2.0以上の時
	if (m_deleteTimer >= 2.0f)
	{
		DeleteGO(this);																	//	自身を削除
	}
}

void Bullet::Render(RenderContext& rc) {
	m_render.Draw(rc);
}

void Bullet::Move() {
	m_position += m_moveSpeed;
	m_render.SetPosition(m_position);
	m_render.Update();
}