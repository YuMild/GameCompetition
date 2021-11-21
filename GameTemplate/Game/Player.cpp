#include "stdafx.h"
#include "Player.h"

#include "Enemy.h"
#include "Bullet.h"
#include "Shine.h"
#include "Wind.h"

Player::Player() {

}

Player::~Player() {

}

bool Player::Start() {
	//アニメーションファイル
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_render.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);

	//当たり判定
	m_characterController.Init(20.0f, 5.0f, m_position);

	//音声
	g_soundEngine->ResistWaveFileBank(8, "Assets/sound/damage1.wav");
	g_soundEngine->ResistWaveFileBank(9, "Assets/sound/damage2.wav");
	g_soundEngine->ResistWaveFileBank(10, "Assets/sound/damage3.wav");

	//描画
	m_render.SetPosition(m_position);//初期値だから実は書かなくてもいい
	m_position.x = 0.0f;//初期値だから実は書かなくてもいい
	m_position.y = 0.0f;//初期値だから実は書かなくてもいい
	m_position.z = 0.0f;//初期値だから実は書かなくてもいい
	m_render.SetScale({ 0.7f,0.7f,0.7f });//初期値だから実は書かなくてもいい
	m_render.Update();

	return true;
}

void Player::Update(){
	Move();
	ManageState();
	PlayAnimation();
	Rotation();
	m_render.Update();
}

void Player::Render(RenderContext& rc) {

	m_render.Draw(rc);
}

void Player::Move() {

	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	float lStickX = g_pad[0]->GetLStickXF();
	float lStickY = g_pad[0]->GetLStickYF();

	Vector3 cameraForward = g_camera3D->GetForward();//前後
	Vector3 cameraRight = g_camera3D->GetRight();//左右
	cameraForward.y = 0.0f;//上には動かないように
	cameraRight.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.Normalize();
	m_moveSpeed += cameraForward * lStickY * 150.0f;//前後
	m_moveSpeed += cameraRight * lStickX * 150.0f;//左右

	if (m_characterController.IsOnGround()) {//キャラが地面に立っている時
		m_moveSpeed.y = 0.0f;//上には動かない
	}
	else {
		m_moveSpeed.y -= 2.5f;//落下スピード
	}

	//通常攻撃

	m_bulletCoolTimer += g_gameTime->GetFrameDeltaTime();

	if (m_bulletCoolTimer > 1.0f) {//射出してから1秒
		m_bulletMagazine = true;//クールタイムを非活性化
	}

	//クールタイム非活性化時
	if (g_pad[0]->IsTrigger(enButtonRB1) && m_bulletMagazine == true)
	{
		m_bullet = NewGO<Bullet>(0, "bullet");//砲丸を生成
		m_bulletCoolTimer = 0;//クールタイマーのリセット
		m_bulletMagazine = false;//クールタイムを活性化
	}

	//光魔法

	m_shineCoolTimer += g_gameTime->GetFrameDeltaTime();

	if (m_shineCoolTimer > 15.0f) {//射出してから1秒
		m_shineMagazine = true;//クールタイムを非活性化
	}

	//クールタイム非活性化時
	if (g_pad[0]->IsTrigger(enButtonY) && m_shineMagazine == true)
	{
		m_shine = NewGO<Shine>(0, "shine");//光魔法を生成
		m_shineCoolTimer = 0;//クールタイマーのリセットaa
		m_shineMagazine = false;//クールタイムを活性化
	}

	//風魔法

	m_windCoolTimer += g_gameTime->GetFrameDeltaTime();

	if (m_windCoolTimer > 10.0f) {//射出してから1秒
		m_windMagazine = true;//クールタイムを非活性化
	}

	//クールタイム非活性化時
	if (g_pad[0]->IsTrigger(enButtonA) && m_windMagazine == true)
	{
		m_wind = NewGO<Wind>(0, "wind");//風魔法を生成
		m_windCoolTimer = 0;//クールタイマーのリセット
		m_windMagazine = false;//クールタイムを活性化
	}

	//瞬間移動魔法

	m_brinkCoolTimer += g_gameTime->GetFrameDeltaTime();

	//クールタイム活性化
	if (m_brinkCoolTimer >= 7.0f) {
		m_brinkMagazine = true;
	}

	if (g_pad[0]->IsTrigger(enButtonLB1) && m_brinkMagazine == true) {

		m_brinkCoolTimer = 0.0f;
		m_brinkMagazine = false;

		if (m_brinkCoolTimer < 0.2f) {
			m_moveSpeed += cameraForward * 20000.0f;
		}
	}

	//死亡判定//
	const auto& enemyList = FindGOs<Enemy>("Enemy");
	for (auto enemy : enemyList)
	{
		Vector3 unitydiff = m_position - enemy->GetPosition();
		if (unitydiff.Length() <= 10.0f) {
			if (m_hp >= 1) {
				m_hp -= 1;
				DeleteGO(enemy);
			}
		}
	}

	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_render.SetPosition(m_position);
	ManageState();
}

void Player::Rotation() {
	//プレイヤーの回転
	Vector3 forward = g_camera3D->GetForward();
	forward.y = 0.0f;
	forward.Normalize();
	Quaternion quaternion;
	quaternion.SetRotationY(atan2f(forward.x, forward.z));
	m_render.SetRotation(quaternion);
}

void Player::ManageState() {
	//プレイヤーの状態
	if (m_characterController.IsOnGround() == false) {
		//プレイヤーが地面の上に立っていない時
		m_playerState = 1;//ジャンプアニメーションを再生する
		return;
	}
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f) {
		//プレイヤーがxzの方向に動いている時
		m_playerState = 2;//歩行アニメーションを再生する
	}
	else {//上以外の時
		m_playerState = 0;//立ちアニメーションを再生する
	}
	switch (m_hp) {
	case 0:
		if (m_1Damage == true) {
			m_damage1SE = NewGO<SoundSource>(10);
			m_damage1SE->Init(10);
			m_damage1SE->Play(false);
			m_1Damage = false;
			DeleteGO(this);
		}
		break;
	case 1:
		if (m_2Damage == true) {
			m_damage1SE = NewGO<SoundSource>(9);
			m_damage1SE->Init(9);
			m_damage1SE->Play(false);
			m_2Damage = false;
		}
		break;
	case 2:
		if (m_3Damage == true) {
			m_damage1SE = NewGO<SoundSource>(8);
			m_damage1SE->Init(8);
			m_damage1SE->Play(false);
			m_3Damage = false;
		}
		break;
	case 3:
		break;
	}
}

void Player::PlayAnimation() {
	//プレイヤーの状態の描画
	switch (m_playerState) {
	case 0://プレイヤーが地面の上で静止している時
		m_render.PlayAnimation(enAnimationClip_Idle);
		break;
	case 1://プレイヤーが地面の上に立っていない時
		m_render.PlayAnimation(enAnimationClip_Jump);
		break;
	case 2://プレイヤーがxzの方向に動いている時
		m_render.PlayAnimation(enAnimationClip_Walk);
		break;
	}
}