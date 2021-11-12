#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "Game.h"
#include "Background.h"
#include "sound/SoundEngine.h"

Bullet::Bullet() {
}
Bullet:: ~Bullet() {
}
bool Bullet::Start() {

	player = FindGO<Player>("player");
	render.Init("Assets/modelData/bullet.tkm");//レンダー
	render.SetScale({ 0.35f,0.35f,0.35f });//サイズ
	position = player->GetPosition();//プレイヤーの場所に生まれる
	position.y += 0.0f;//プレイヤーの20f上に生まれる

	direction = g_camera3D->GetForward();
	direction.y = 0.0f;
	direction.Normalize();

	moveSpeed = direction * 5.0f;

	return true;
}

void Bullet::Update() {

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
	direction += moveSpeed;//砲丸のスピード(重要)
	render.SetPosition(direction);//描画する位置
	render.Update();//描画の更新
}