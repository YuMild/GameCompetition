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
	m_render.Init("Assets/modelData/bullet.tkm");//レンダー
	m_render.SetScale({ 0.5f,0.5f,0.5f });//サイズ
	m_position = m_player->GetPosition();//プレイヤーの場所に生まれる
	m_position.y += 50.0f;//プレイヤーの50f上に生まれる

	//余裕が出来たらやる
	//コリジョンの生成
	//collisionObject = NewGO<CollisionObject>(0);
	//Vector3 collisionPosition = m_position;
	//collisionObject->CreateSphere(collisionPosition);
	//collisionObject->SetName("bullet");

	//エフェクトファイル
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/fireball.efk");

	//方向
	m_forward = g_camera3D->GetForward();
	m_forward.y = 0.0f;
	m_forward.Normalize();

	//エフェクト
	m_fireBallEF = NewGO<EffectEmitter>(0);
	m_fireBallEF->Init(0);
	m_fireBallEF->SetScale(Vector3::One * 20.0f);
	m_fireBallEF->Play();

	//音声
	m_gunShotSE = NewGO<SoundSource>(6);
	m_gunShotSE->Init(6);
	m_gunShotSE->Play(false);

	m_moveSpeed = m_forward * 20.0f;

	return true;
}

void Bullet::Update() {

	m_fireBallEF->SetPosition(m_position);

	Move();//Move関数を更新する
	m_deleteTimer += g_gameTime->GetFrameDeltaTime();

	//タイマーが2.0以上になったら。
	if (m_deleteTimer >= 2.0f)
	{
		//自身を削除。
		DeleteGO(this);
	}
}

void Bullet::Render(RenderContext& rc) {
	m_render.Draw(rc);//描画の元
}

void Bullet::Move() {
	m_position += m_moveSpeed;//砲丸のスピード(重要)
	m_render.SetPosition(m_position);//描画する位置
	m_render.Update();//描画の更新
}