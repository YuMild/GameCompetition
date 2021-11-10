#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Hougan.h"
#include "Background.h"
#include "sound/SoundEngine.h"
#include "graphics/effect/EffectEmitter.h"

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
	playerrender.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);

	//エフェクトファイル
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/explosion.efk");

	characterController.Init(20.0f, 5.0f, playerposition);//当たり判定

	playerrender.SetPosition(playerposition);//場所
	playerposition.x = 0.0f;//左右
	playerposition.y = 35.0f;//上下
	playerposition.z = 0.0f;//前後

	playerrender.SetScale({ 0.5f,0.5f,0.5f });//サイズ
	playerrender.Update();//上の情報を更新する

	//音声ファイル
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/gunshot.wav");
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/dryfire.wav");
	g_soundEngine->ResistWaveFileBank(7, "Assets/sound/enemydeath.wav");

	return true;
}

void Player::Update() {
	//情報の更新
	playerrender.Update();
	Move();
	ManageState();
	PlayAnimation();
	Rotation();
}

void Player::Render(RenderContext& rc) {
	//描画の元
	playerrender.Draw(rc);
}

void Player::Move() {

	//キャラコン
	Vector3 stickL;//スティックの入力
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();
	Vector3 forward = g_camera3D->GetForward();//前後
	Vector3 right = g_camera3D->GetRight();//左右
	forward.y = 0.0f;//上には動かないように
	right.y = 0.0f;
	forward.Normalize();
	right.Normalize();
	forward *= stickL.y * 30.0f;//前後
	right *= stickL.x * 30.0f;//左右

	playerMoveSpeed.x = 0.0f;//初期化
	playerMoveSpeed.z = 0.0f;

	playerMoveSpeed += right + forward;//全体の動く方向

	if (characterController.IsOnGround()) {//キャラが地面に立っている時
		playerMoveSpeed.y = 0.0f;//上には動かない
	}
	else {
		playerMoveSpeed.y -= 2.5f;//落下スピード
	}

	playerposition = characterController.Execute(playerMoveSpeed, 1.0f / 30.0f);//キャラクターポジションに当たり判定を追従させる
	playerrender.SetPosition(playerposition);//描画する位置

	//発射クールタイム
	cooltimer += g_gameTime->GetFrameDeltaTime();

	if (cooltimer > 1.0f) {//発射してから1秒
		cooltime = true;//再度発射できるようになる
	}

	//砲丸の発射
	if (g_pad[0]->IsTrigger(enButtonLB1)) {//クールタイムが0の時
		if (cooltime == true) {
			m_hougan = NewGO<Hougan>(0, "hougan");//砲丸を生み出す
			cameraposition = g_camera3D->GetForward();//上には動かないように
			cameraposition.y = 0.0f;
			cameraposition.Normalize();
			m_hougan->moveSpeed = cameraposition * 6.5f;//砲丸の移動する方向
			cooltimer = 0;//クールタイマーの初期化
			cooltime = false;//クールタイムを発動
			m_hougan->houganposition = playerposition;
			gunshotSE = NewGO<SoundSource>(5);
			gunshotSE->Init(5);
			gunshotSE->Play(false);
		}
		else if (cooltime == false) {//クールタイムが0じゃない時
			dryfireSE = NewGO<SoundSource>(6);
			dryfireSE->Init(6);
			dryfireSE->Play(false);
		}
	}

	//敵の死亡判定
	const auto& enemyList = FindGOs<Enemy>("Enemy");
	const auto& houganList = FindGOs<Hougan>("hougan");
	for (auto hougan : houganList) {

		for (auto enemy : enemyList)
		{
			Vector3 hougandiff = hougan->houganposition - enemy->enemyposition;

			if (hougandiff.Length() <= 50.0f) {
				EffectEmitter* shockEF = NewGO<EffectEmitter>(0);
				shockEF->Init(0);
				shockEF->SetPosition(m_hougan->houganposition);
				shockEF->SetScale(Vector3::One * 5.0f);
				shockEF->Play();
				DeleteGO(enemy);
				enemydeathSE = NewGO<SoundSource>(7);
				enemydeathSE->Init(7);
				enemydeathSE->Play(false);
			}
		}
	}
}

void Player::Rotation() {
	//プレイヤーの回転
	if (fabsf(playerMoveSpeed.x) >= 0.001f || fabsf(playerMoveSpeed.z) >= 0.001f) {
		playerrotation.SetRotationYFromDirectionXZ(playerMoveSpeed);
		m_forward = Vector3::AxisZ;//分かんない
		playerrotation.Apply(m_forward);//プレイヤーが向いている方向(?)
	}

	Vector3 forward = g_camera3D->GetForward();
	forward.y = 0.0f;
	forward.Normalize();
	Quaternion rotation;
	rotation.SetRotationY(atan2f(forward.x, forward.z));
	playerrender.SetRotation(rotation);
}

void Player::ManageState() {
	//プレイヤーの状態
	if (characterController.IsOnGround() == false) {
		//プレイヤーが地面の上に立っていない時
		playerState = 1;//ジャンプアニメーションを再生する
		return;
	}
	if (fabsf(playerMoveSpeed.x) >= 0.001f || fabsf(playerMoveSpeed.z) >= 0.001f) {
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
		playerrender.PlayAnimation(enAnimationClip_Idle);
		break;
	case 1://プレイヤーが地面の上に立っていない時
		playerrender.PlayAnimation(enAnimationClip_Jump);
		break;
	case 2://プレイヤーがxzの方向に動いている時
		playerrender.PlayAnimation(enAnimationClip_Walk);
		break;
	}
}