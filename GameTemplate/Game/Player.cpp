#include "stdafx.h"
#include "Player.h"

#include "Enemy.h"
#include "Bullet.h"
#include "Fire.h"
#include "Game.h"
#include "Hp.h"
#include "Mp.h"
#include "Shine.h"
#include "Water.h"
#include "Wind.h"

namespace {
	
}

Player::Player() 
{

}

Player::~Player()
{

}

bool Player::Start() 
{
	//アニメーションファイル
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/Idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/Walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_animationClips[enAnimationClip_kneelDown].Load("Assets/animData/kneelDown.tka");
	m_animationClips[enAnimationClip_kneelDown].SetLoopFlag(false);
	m_render.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);

	//当たり判定
	m_characterController.Init(20.0f, 5.0f, m_position);

	//音声
	g_soundEngine->ResistWaveFileBank(8, "Assets/sound/damage1.wav");
	g_soundEngine->ResistWaveFileBank(9, "Assets/sound/damage2.wav");
	g_soundEngine->ResistWaveFileBank(10, "Assets/sound/damage3.wav");

	EffectEngine::GetInstance()->ResistEffect2D(100, u"Assets/effect/CoolTimeCompleteFire.efk");
	EffectEngine::GetInstance()->ResistEffect2D(101, u"Assets/effect/CoolTimeCompleteWater.efk");
	EffectEngine::GetInstance()->ResistEffect2D(102, u"Assets/effect/CoolTimeCompleteWind.efk");
	EffectEngine::GetInstance()->ResistEffect2D(103, u"Assets/effect/CoolTimeCompleteShine.efk");

	//描画
	m_render.SetPosition(m_position);//初期値だから実は書かなくてもいい
	m_position.x = 0.0f;//初期値だから実は書かなくてもいい
	m_position.y = 0.0f;//初期値だから実は書かなくてもいい
	m_position.z = 0.0f;//初期値だから実は書かなくてもいい
	m_render.SetScale({ 0.7f,0.7f,0.7f });//初期値だから実は書かなくてもいい
	m_render.Update();

	m_game = FindGO<Game>("game");
	m_hp = FindGO<Hp>("hp");
	m_mp = FindGO<Mp>("mp");

	return true;
}

void Player::Update()
{
	if (m_game->GetManageState() == 0)
	{
		Magic();
		Move();
		Timer();
		Rotation();
	}
	else
	{
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.y = 0.0f;
		m_moveSpeed.z = 0.0f;
	}
	ManageState();
	PlayAnimation();
	m_render.Update();
}

void Player::Timer() 
{
	m_bulletCoolTimer += g_gameTime->GetFrameDeltaTime();
	if (m_bulletCoolTimer > COOLTIME_BULLET) {//クールタイムが非活性化且つMPが必要以上の時
		m_bulletMagazine = true;//クールタイムを非活性化
	}
	m_fireCoolTimer += g_gameTime->GetFrameDeltaTime();
	if (m_fireMagazine == false && m_fireCoolTimer > COOLTIME_FIRE && m_mp->GetMP() >= MP_FIRE) {//クールタイムが非活性化且つMPが必要以上の時
		m_fireMagazine = true;//クールタイムを非活性化
		m_coolTimeCompleteFireEF = NewGO<EffectEmitter>(100);
		m_coolTimeCompleteFireEF->Init2D(100);
		m_coolTimeCompleteFireEF->SetScale(Vector3::One * 5.0f);
		m_coolTimeCompleteFireEF->SetPosition(Vector3{ 700.0f,-225.0f,0.0f });
		m_coolTimeCompleteFireEF->Play2D();
	}
	m_waterCoolTimer += g_gameTime->GetFrameDeltaTime();
	if (m_waterMagazine == false && m_waterCoolTimer > COOLTIME_WATER && m_mp->GetMP() >= MP_WATER) {//クールタイムが非活性化且つMPが必要以上の時
		m_waterMagazine = true;//クールタイムを非活性化
		m_coolTimeCompleteWaterEF = NewGO<EffectEmitter>(101);
		m_coolTimeCompleteWaterEF->Init2D(101);
		m_coolTimeCompleteWaterEF->SetScale(Vector3::One * 5.0f);
		m_coolTimeCompleteWaterEF->SetPosition(Vector3{ 536.0f,-225.0f,0.0f });
		m_coolTimeCompleteWaterEF->Play2D();
	}
	m_windCoolTimer += g_gameTime->GetFrameDeltaTime();
	if (m_windMagazine == false && m_windCoolTimer > COOLTIME_WIND && m_mp->GetMP() >= MP_WIND) {//クールタイムが非活性化且つMPが必要以上の時
		m_windMagazine = true;//クールタイムを非活性化
		m_coolTimeCompleteWindEF = NewGO<EffectEmitter>(102);
		m_coolTimeCompleteWindEF->Init2D(102);
		m_coolTimeCompleteWindEF->SetScale(Vector3::One * 5.0f);
		m_coolTimeCompleteWindEF->SetPosition(Vector3{ 618.0f, -310.0f, 0.0f });
		m_coolTimeCompleteWindEF->Play2D();
	}
	m_shineCoolTimer += g_gameTime->GetFrameDeltaTime();
	if (m_shineMagazine == false && m_shineCoolTimer > COOLTIME_SHINE && m_mp->GetMP() >= MP_SHINE) {//クールタイムが非活性化且つMPが必要以上の時
		m_shineMagazine = true;//クールタイムを非活性化
		m_coolTimeCompleteShineEF = NewGO<EffectEmitter>(103);
		m_coolTimeCompleteShineEF->Init2D(103);
		m_coolTimeCompleteShineEF->SetScale(Vector3::One * 5.0f);
		m_coolTimeCompleteShineEF->SetPosition(Vector3{ 618.0f, -140.0f, 0.0f });
		m_coolTimeCompleteShineEF->Play2D();
	}
}

void Player::Render(RenderContext& rc)
{
	m_render.Draw(rc);
}

void Player::Move()
{
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
	if (m_hp->GetHP() >= 1) {
		m_moveSpeed += m_cameraForward * lStickY * 170.0f;//前後
		m_moveSpeed += m_cameraRight * lStickX * 170.0f;//左右
	}

	//水魔法
	//クールタイム非活性化時
	if (g_pad[0]->IsTrigger(enButtonX) && m_waterMagazine == true)
	{
		m_water = NewGO<Water>(0, "water");
		//クールタイム
		m_waterCoolTimer = 0.0f;
		m_waterExeTimer = 0.0f;
		m_waterMagazine = false;
		m_waterIsExe = true;
		//MP減算
		m_mp->SubMp(MP_WATER);
	}

	//発動までの時間
	if (m_waterMagazine == false);
	{
		m_waterExeTimer += g_gameTime->GetFrameDeltaTime();
		if (m_waterExeTimer > 1.0f && m_waterIsExe == true)
		{
			m_moveSpeed += m_cameraForward * 20000.0f;
			m_waterIsExe = false;
		}
	}

	if (m_characterController.IsOnGround()) {//キャラが地面に立っている時
		m_moveSpeed.y = 0.0f;//上には動かない
	}
	else {
		m_moveSpeed.y -= 10.0f;//落下スピード
	}

	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_render.SetPosition(m_position);
	ManageState();
}

void Player::Magic()
{
	//通常攻撃
	//クールタイム非活性化時
	if (g_pad[0]->IsTrigger(enButtonRB2) && m_bulletMagazine == true)
	{
		m_bullet = NewGO<Bullet>(0, "bullet");//砲丸を生成
		m_bullet->SetPosition(m_position);//最初の1fだけステージ中央に判定が生じるのを防ぐ
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
		m_mp->SubMp(MP_FIRE);
	}

	//風魔法
	//クールタイム非活性化時
	if (g_pad[0]->IsTrigger(enButtonA) && m_windMagazine == true)
	{
		m_wind = NewGO<Wind>(0, "wind");//風魔法を生成
		m_windCoolTimer = 0;//クールタイマーのリセット
		m_windMagazine = false;//クールタイムを活性化
		m_mp->SubMp(MP_WIND);
	}

	//光魔法
	//クールタイム非活性化時
	if (g_pad[0]->IsTrigger(enButtonY) && m_shineMagazine == true)
	{
		m_shine = NewGO<Shine>(0, "shine");//光魔法を生成
		m_shineCoolTimer = 0;//クールタイマーのリセット
		m_shineMagazine = false;//クールタイムを活性化
		m_mp->SubMp(MP_SHINE);
	}
}

void Player::Rotation() 
{
	//プレイヤーの回転
	Vector3 forward = g_camera3D->GetForward();
	forward.y = 0.0f;
	forward.Normalize();
	Quaternion quaternion;
	quaternion.SetRotationY(atan2f(forward.x, forward.z));
	if (m_hp->GetHP() >= 1) {
		m_render.SetRotation(quaternion);
	}
}

void Player::ManageState() 
{
	//プレイヤーの状態
	if (m_characterController.IsOnGround() == false) {//プレイヤーが地面の上に立っていない時
		m_moveSpeed.y -= 1.0f;
		m_playerState = 1;//ジャンプアニメーションを再生する
		return;
	}
	if (fabsf(m_moveSpeed.x) >= 0.10f || fabsf(m_moveSpeed.z) >= 0.1f) {//プレイヤーがxzの方向に動いている時
		m_playerState = 2;//歩行アニメーションを再生する
	}
	else if (m_hp->GetHP() <= 0)
	{
		m_playerState = 3;
	}
	else {//上以外の時
		m_playerState = 0;//立ちアニメーションを再生する
	}
}

void Player::PlayAnimation()
{
	//プレイヤーの状態の描画
	switch (m_playerState)
	{
	case 0://プレイヤーが地面の上で静止している時
		m_render.PlayAnimation(enAnimationClip_Idle);
		break;
	case 1://プレイヤーが地面の上に立っていない時
		m_render.PlayAnimation(enAnimationClip_Jump);
		break;
	case 2://プレイヤーがxzの方向に動いている時
		m_render.PlayAnimation(enAnimationClip_Walk);
		break;
	case 3://プレイヤーが死亡した時
		m_render.PlayAnimation(enAnimationClip_kneelDown);
		break;
	}
}