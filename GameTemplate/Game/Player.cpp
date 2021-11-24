#include "stdafx.h"
#include "Player.h"

#include "Enemy.h"
#include "Bullet.h"
#include "Fire.h"
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

	EffectEngine::GetInstance()->ResistEffect(6, u"Assets/effect/MagicCircleBrink.efk");

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
	Magic();
	Move();
	Timer();
	Death();
	ManageState();
	PlayAnimation();
	Rotation();
	m_render.Update();
}

void Player::Timer() {

	m_bulletCoolTimer += g_gameTime->GetFrameDeltaTime();
	if (m_bulletCoolTimer > 1.0f) {//射出してから1秒
		m_bulletMagazine = true;//クールタイムを非活性化
	}

	m_fireCoolTimer += g_gameTime->GetFrameDeltaTime();
	if (m_fireCoolTimer > 10.0f) {//射出してから10秒
		m_fireMagazine = true;//クールタイムを非活性化
	}

	m_windCoolTimer += g_gameTime->GetFrameDeltaTime();
	if (m_windCoolTimer > 15.0f) {//射出してから15秒
		m_windMagazine = true;//クールタイムを非活性化
	}

	m_shineCoolTimer += g_gameTime->GetFrameDeltaTime();
	if (m_shineCoolTimer > 20.0f) {//射出してから20秒
		m_shineMagazine = true;//クールタイムを非活性化
	}

	m_brinkCoolTimer += g_gameTime->GetFrameDeltaTime();
	if (m_brinkCoolTimer > 7.0f) {//射出してから7秒
		m_brinkMagazine = true;//クールタイムを非活性化
	}
}

void Player::Render(RenderContext& rc) {

	m_render.Draw(rc);
}

void Player::Move() {

	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	float lStickX = g_pad[0]->GetLStickXF();
	float lStickY = g_pad[0]->GetLStickYF();

	m_cameraForward = g_camera3D->GetForward();//前後
	m_cameraRight = g_camera3D->GetRight();//左右
	m_cameraForward.y = 0.0f;//上には動かないように
	m_cameraRight.y = 0.0f;
	m_cameraForward.Normalize();
	m_cameraRight.Normalize();
	m_moveSpeed += m_cameraForward * lStickY * 150.0f;//前後
	m_moveSpeed += m_cameraRight * lStickX * 150.0f;//左右

	//瞬間移動魔法
	//クールタイム非活性化時
	if (g_pad[0]->IsTrigger(enButtonLB1) && m_brinkMagazine == true) {
		m_brinkCoolTimer = 0.0f;
		m_brinkMagazine = false;
		m_moveSpeed += m_cameraForward * 20000.0f;
		m_brinkEF = NewGO<EffectEmitter>(6);
		m_brinkEF->Init(6);
		m_brinkEF->SetScale(Vector3::One * 50.0f);
		m_brinkEF->Play();
	}
	if (m_brinkMagazine == false && m_brinkCoolTimer <= 0.8f) {
		m_magicCirclePosition = m_position;
		m_magicCirclePosition.y = 10.0f;
		
		m_brinkEF->SetPosition(m_magicCirclePosition);
	}

	if (m_characterController.IsOnGround()) {//キャラが地面に立っている時
		m_moveSpeed.y = 0.0f;//上には動かない
	}
	else {
		m_moveSpeed.y -= 2.5f;//落下スピード
	}

	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_render.SetPosition(m_position);
	ManageState();
}

void Player::Magic() {

	//通常攻撃
	//クールタイム非活性化時
	if (g_pad[0]->IsTrigger(enButtonRB1) && m_bulletMagazine == true)
	{
		m_bullet = NewGO<Bullet>(0, "bullet");//砲丸を生成
		m_bullet->SetPosition(m_position);
		m_bulletCoolTimer = 0;//クールタイマーのリセット
		m_bulletMagazine = false;//クールタイムを活性化
	}

	//炎魔法
	//クールタイム非活性化時
	if (g_pad[0]->IsTrigger(enButtonB) && m_fireMagazine == true)
	{
		m_fire = NewGO<Fire>(0, "fire");//炎魔法を生成
		m_fireCoolTimer = 0;//クールタイムのリセット
		m_fireMagazine = false;//クールタイムを活性化
	}

	//光魔法
	//クールタイム非活性化時
	if (g_pad[0]->IsTrigger(enButtonY) && m_shineMagazine == true)
	{
		m_shine = NewGO<Shine>(0, "shine");//光魔法を生成
		m_shineCoolTimer = 0;//クールタイマーのリセット
		m_shineMagazine = false;//クールタイムを活性化
	}

	//風魔法
	//クールタイム非活性化時
	if (g_pad[0]->IsTrigger(enButtonA) && m_windMagazine == true)
	{
		m_wind = NewGO<Wind>(0, "wind");//風魔法を生成
		m_windCoolTimer = 0;//クールタイマーのリセット
		m_windMagazine = false;//クールタイムを活性化
	}
}

void Player::Death() {

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
		if (m_3Damage == true)
		{
			m_damage3SE = NewGO<SoundSource>(10);
			m_damage3SE->Init(10);
			//m_damage3SE->SetVolume(0.1f);
			m_damage3SE->Play(false);
			m_3Damage = false;
			DeleteGO(this);
		}
		break;
	case 1:
		if (m_2Damage == true) {
			m_damage2SE = NewGO<SoundSource>(9);
			m_damage2SE->Init(9);
			//m_damage2SE->SetVolume(0.1f);
			m_damage2SE->Play(false);
			m_2Damage = false;
		}
		break;
	case 2:
		if (m_1Damage == true) {
			m_damage1SE = NewGO<SoundSource>(8);
			m_damage1SE->Init(8);
			//m_damage1SE->SetVolume(0.1f);
			m_damage1SE->Play(false);
			m_1Damage = false;
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