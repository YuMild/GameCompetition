#include "stdafx.h"
#include "Player.h"

#include "Bullet.h"
#include "Shine.h"

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

	//描画
	m_render.SetPosition(m_position);//初期値だから実は書かなくてもいい
	m_position.x = 0.0f;//初期値だから実は書かなくてもいい
	m_position.y = 0.0f;//初期値だから実は書かなくてもいい
	m_position.z = 0.0f;//初期値だから実は書かなくてもいい
	m_render.SetScale({ 1.0f,1.0f,1.0f });//初期値だから実は書かなくてもいい
	m_render.Update();

	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/shine.efk");

	return true;
}

void Player::Update(){

	m_render.Update();
	Move();
	ManageState();
	PlayAnimation();
	Rotation();
}

void Player::Render(RenderContext& rc) {

	m_render.Draw(rc);
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

	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	m_moveSpeed += right + forward;

	if (m_characterController.IsOnGround()) {//キャラが地面に立っている時
		m_moveSpeed.y = 0.0f;//上には動かない
	}
	else {
		m_moveSpeed.y -= 2.5f;//落下スピード
	}

	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 30.0f);
	m_render.SetPosition(m_position);

	//通常攻撃

	m_bulletCoolTimer += g_gameTime->GetFrameDeltaTime();

	if (m_bulletCoolTimer > 1.0f) {//射出してから1秒
		m_bulletMagazine = true;//クールタイムを非活性化
	}
	
	if (g_pad[0]->IsTrigger(enButtonLB1)) {//クールタイム非活性化時
		if (m_bulletMagazine == true) {
			m_bullet = NewGO<Bullet>(0, "bullet");//砲丸を生成
			m_bulletCoolTimer = 0;//クールタイマーのリセット
			m_bulletMagazine = false;//クールタイムを活性化
		}
		else if (m_bulletMagazine == false) {//クールタイム活性化時
			m_dryFireSE = NewGO<SoundSource>(6);
			m_dryFireSE->Init(6);
			m_dryFireSE->Play(false);
		}
	}

	//光魔法

	m_shineCoolTimer += g_gameTime->GetFrameDeltaTime();

	if (m_shineCoolTimer > 15.0f) {//射出してから1秒
		m_shineMagazine = true;//クールタイムを非活性化
	}

	if (g_pad[0]->IsTrigger(enButtonY)) {//クールタイム非活性化時
		if (m_shineMagazine == true) {
			m_shine = NewGO<Shine>(0, "shine");//光魔法を生成
			m_shineSE = NewGO<SoundSource>(7);
			m_shineSE->Init(7);
			m_shineSE->Play(false);
			m_shineCoolTimer = 0;//クールタイマーのリセット
			m_shineMagazine = false;//クールタイムを活性化
		}
	}
}

void Player::Rotation() {
	//プレイヤーの回転
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f) {
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		m_forward = Vector3::AxisZ;//分かんない
		m_rotation.Apply(m_forward);//プレイヤーが向いている方向(?)
	}

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