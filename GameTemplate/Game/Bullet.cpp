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
	bulletRender.Init("Assets/modelData/hougan.tkm");//レンダー
	bulletRender.SetScale({ 0.35f,0.35f,0.35f });//サイズ
	bulletPosition = player->playerPosition;//プレイヤーの場所に生まれる
	bulletPosition.y += 25.0f;//プレイヤーの20f上に生まれる


	return true;
}
void Bullet::Update() {
	Move();//Move関数を更新する
	deleteTimer += g_gameTime->GetFrameDeltaTime();

	//タイマーが2.0以上になったら。
	if (deleteTimer >= 2.0f)
	{
		//自身を削除。
		DeleteGO(this);
	}
}
void Bullet::Render(RenderContext& rc) {
	bulletRender.Draw(rc);//描画の元
}
void Bullet::Move() {
	bulletPosition += bulletMoveSpeed;//砲丸のスピード(重要)
	bulletRender.SetPosition(bulletPosition);//描画する位置
	bulletRender.Update();//描画の更新
}