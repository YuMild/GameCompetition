#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "Game.h"
#include "Background.h"
#include "sound/SoundEngine.h"
#include "graphics/effect/EffectEmitter.h"

Bullet::Bullet() {
}
Bullet:: ~Bullet() {
}
bool Bullet::Start() {

	player = FindGO<Player>("player");
	render.Init("Assets/modelData/bullet.tkm");//レンダー
	render.SetScale({ 0.5f,0.5f,0.5f });//サイズ
	position = player->GetPosition();//プレイヤーの場所に生まれる
	position.y += 50.0f;//プレイヤーの50f上に生まれる

	//エフェクトファイル
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/fireball.efk");

	//方向
	direction = g_camera3D->GetForward();
	direction.y = 0.0f;
	direction.Normalize();

	fireBallEF = NewGO<EffectEmitter>(0);
	fireBallEF->Init(0);
	
	fireBallEF->SetScale(Vector3::One * 20.0f);
	fireBallEF->Play();

	moveSpeed = direction * 20.0f;

	return true;
}

void Bullet::Update() {

	fireBallEF->SetPosition(position);

	Move();//Move関数を更新する
	deletetimer += g_gameTime->GetFrameDeltaTime();

	//タイマーが2.0以上になったら。
	if (deletetimer >= 2.0f)
	{
		//自身を削除。
		DeleteGO(this);
	}
}

void Bullet::Render(RenderContext& rc) {
	render.Draw(rc);//描画の元
}

void Bullet::Move() {
	position += moveSpeed;//砲丸のスピード(重要)
	render.SetPosition(position);//描画する位置
	render.Update();//描画の更新
}