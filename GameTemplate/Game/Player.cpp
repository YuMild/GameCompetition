#include "stdafx.h"
#include "Player.h"

#include "Bullet.h"

Player::Player() {

}

Player::~Player() {

}

bool Player::Start() {
	//アニメーションファイル
	animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	render.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);

	characterController.Init(20.0f, 5.0f, position);//当たり判定

	render.SetPosition(position);
	position.x = 0.0f;
	position.y = 35.0f;
	position.z = 0.0f;

	render.SetScale({ 1.0f,1.0f,1.0f });
	render.Update();

	return true;
}

void Player::Update(){

	render.Update();
	Move();
	ManageState();
	PlayAnimation();
	Rotation();
}

void Player::Render(RenderContext& rc) {

	render.Draw(rc);
}

void Player::Move() {

	//キャラコン
	Vector3 stickL;//スティックの入力
	stickL.y = g_pad[0]->GetLStickYF();
	stickL.x = g_pad[0]->GetLStickXF();
	Vector3 forward = g_camera3D->GetForward();//前後
	Vector3 right = g_camera3D->GetRight();//左右
	forward.y = 0.0f;//上には動かないように
	right.y = 0.0f;
	forward.Normalize();
	right.Normalize();
	forward *= stickL.y * 150.0f;//前後
	right *= stickL.x * 150.0f;//左右

	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;

	moveSpeed += right + forward;

	if (characterController.IsOnGround()) {//キャラが地面に立っている時
		moveSpeed.y = 0.0f;//上には動かない
	}
	else {
		moveSpeed.y -= 2.5f;//落下スピード
	}

	position = characterController.Execute(moveSpeed, 1.0f / 30.0f);
	render.SetPosition(position);

	//発射クールタイム
	cooltimer += g_gameTime->GetFrameDeltaTime();

	if (cooltimer > 1.0f) {//発射してから1秒
		magazine = true;//再度発射できるようになる
	}

	//砲丸の発射
	if (g_pad[0]->IsTrigger(enButtonLB1)) {//クールタイムが0の時
		if (magazine == true) {
			bullet = NewGO<Bullet>(0, "bullet");//砲丸を生み出す
			gunShotSE = NewGO<SoundSource>(5);
			gunShotSE->Init(5);
			gunShotSE->Play(false);
		}
		else if (magazine == false) {//クールタイムが0じゃない時
			dryFireSE = NewGO<SoundSource>(6);
			dryFireSE->Init(6);
			dryFireSE->Play(false);
		}
	}
}

void Player::Rotation() {
	//プレイヤーの回転
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f) {
		rotation.SetRotationYFromDirectionXZ(moveSpeed);
		forward = Vector3::AxisZ;//分かんない
		rotation.Apply(forward);//プレイヤーが向いている方向(?)
	}

	Vector3 forward = g_camera3D->GetForward();
	forward.y = 0.0f;
	forward.Normalize();
	Quaternion rotation;
	rotation.SetRotationY(atan2f(forward.x, forward.z));
	render.SetRotation(rotation);
}

void Player::ManageState() {
	//プレイヤーの状態
	if (characterController.IsOnGround() == false) {
		//プレイヤーが地面の上に立っていない時
		playerState = 1;//ジャンプアニメーションを再生する
		return;
	}
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f) {
		//プレイヤーがxzの方向に動いている時
		playerState = 2;//歩行アニメーションを再生する
	}
	else {//上以外の時
		playerState = 0;//立ちアニメーションを再生する
	}
}

void Player::PlayAnimation() {
	//プレイヤーの状態の描画
	switch (playerState) {
	case 0://プレイヤーが地面の上で静止している時
		render.PlayAnimation(enAnimationClip_Idle);
		break;
	case 1://プレイヤーが地面の上に立っていない時
		render.PlayAnimation(enAnimationClip_Jump);
		break;
	case 2://プレイヤーがxzの方向に動いている時
		render.PlayAnimation(enAnimationClip_Walk);
		break;
	}
}