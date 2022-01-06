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
	//�A�j���[�V�����t�@�C��
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/Idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/Walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_animationClips[enAnimationClip_kneelDown].Load("Assets/animData/kneelDown.tka");
	m_animationClips[enAnimationClip_kneelDown].SetLoopFlag(false);
	m_render.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);

	//�����蔻��
	m_characterController.Init(20.0f, 5.0f, m_position);

	//����
	g_soundEngine->ResistWaveFileBank(8, "Assets/sound/damage1.wav");
	g_soundEngine->ResistWaveFileBank(9, "Assets/sound/damage2.wav");
	g_soundEngine->ResistWaveFileBank(10, "Assets/sound/damage3.wav");

	EffectEngine::GetInstance()->ResistEffect2D(100, u"Assets/effect/CoolTimeCompleteFire.efk");
	EffectEngine::GetInstance()->ResistEffect2D(101, u"Assets/effect/CoolTimeCompleteWater.efk");
	EffectEngine::GetInstance()->ResistEffect2D(102, u"Assets/effect/CoolTimeCompleteWind.efk");
	EffectEngine::GetInstance()->ResistEffect2D(103, u"Assets/effect/CoolTimeCompleteShine.efk");

	//�`��
	m_render.SetPosition(m_position);//�����l��������͏����Ȃ��Ă�����
	m_position.x = 0.0f;//�����l��������͏����Ȃ��Ă�����
	m_position.y = 0.0f;//�����l��������͏����Ȃ��Ă�����
	m_position.z = 0.0f;//�����l��������͏����Ȃ��Ă�����
	m_render.SetScale({ 0.7f,0.7f,0.7f });//�����l��������͏����Ȃ��Ă�����
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
	if (m_bulletCoolTimer > COOLTIME_BULLET) {//�N�[���^�C�����񊈐�������MP���K�v�ȏ�̎�
		m_bulletMagazine = true;//�N�[���^�C����񊈐���
	}
	m_fireCoolTimer += g_gameTime->GetFrameDeltaTime();
	if (m_fireMagazine == false && m_fireCoolTimer > COOLTIME_FIRE && m_mp->GetMP() >= MP_FIRE) {//�N�[���^�C�����񊈐�������MP���K�v�ȏ�̎�
		m_fireMagazine = true;//�N�[���^�C����񊈐���
		m_coolTimeCompleteFireEF = NewGO<EffectEmitter>(100);
		m_coolTimeCompleteFireEF->Init2D(100);
		m_coolTimeCompleteFireEF->SetScale(Vector3::One * 5.0f);
		m_coolTimeCompleteFireEF->SetPosition(Vector3{ 700.0f,-225.0f,0.0f });
		m_coolTimeCompleteFireEF->Play2D();
	}
	m_waterCoolTimer += g_gameTime->GetFrameDeltaTime();
	if (m_waterMagazine == false && m_waterCoolTimer > COOLTIME_WATER && m_mp->GetMP() >= MP_WATER) {//�N�[���^�C�����񊈐�������MP���K�v�ȏ�̎�
		m_waterMagazine = true;//�N�[���^�C����񊈐���
		m_coolTimeCompleteWaterEF = NewGO<EffectEmitter>(101);
		m_coolTimeCompleteWaterEF->Init2D(101);
		m_coolTimeCompleteWaterEF->SetScale(Vector3::One * 5.0f);
		m_coolTimeCompleteWaterEF->SetPosition(Vector3{ 536.0f,-225.0f,0.0f });
		m_coolTimeCompleteWaterEF->Play2D();
	}
	m_windCoolTimer += g_gameTime->GetFrameDeltaTime();
	if (m_windMagazine == false && m_windCoolTimer > COOLTIME_WIND && m_mp->GetMP() >= MP_WIND) {//�N�[���^�C�����񊈐�������MP���K�v�ȏ�̎�
		m_windMagazine = true;//�N�[���^�C����񊈐���
		m_coolTimeCompleteWindEF = NewGO<EffectEmitter>(102);
		m_coolTimeCompleteWindEF->Init2D(102);
		m_coolTimeCompleteWindEF->SetScale(Vector3::One * 5.0f);
		m_coolTimeCompleteWindEF->SetPosition(Vector3{ 618.0f, -310.0f, 0.0f });
		m_coolTimeCompleteWindEF->Play2D();
	}
	m_shineCoolTimer += g_gameTime->GetFrameDeltaTime();
	if (m_shineMagazine == false && m_shineCoolTimer > COOLTIME_SHINE && m_mp->GetMP() >= MP_SHINE) {//�N�[���^�C�����񊈐�������MP���K�v�ȏ�̎�
		m_shineMagazine = true;//�N�[���^�C����񊈐���
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

	m_cameraForward = g_camera3D->GetForward();//�O��
	m_cameraRight = g_camera3D->GetRight();//���E
	m_cameraForward.y = 0.0f;//��ɂ͓����Ȃ��悤��
	m_cameraRight.y = 0.0f;
	m_cameraForward.Normalize();
	m_cameraRight.Normalize();
	if (m_hp->GetHP() >= 1) {
		m_moveSpeed += m_cameraForward * lStickY * 170.0f;//�O��
		m_moveSpeed += m_cameraRight * lStickX * 170.0f;//���E
	}

	//�����@
	//�N�[���^�C���񊈐�����
	if (g_pad[0]->IsTrigger(enButtonX) && m_waterMagazine == true)
	{
		m_water = NewGO<Water>(0, "water");
		//�N�[���^�C��
		m_waterCoolTimer = 0.0f;
		m_waterExeTimer = 0.0f;
		m_waterMagazine = false;
		m_waterIsExe = true;
		//MP���Z
		m_mp->SubMp(MP_WATER);
	}

	//�����܂ł̎���
	if (m_waterMagazine == false);
	{
		m_waterExeTimer += g_gameTime->GetFrameDeltaTime();
		if (m_waterExeTimer > 1.0f && m_waterIsExe == true)
		{
			m_moveSpeed += m_cameraForward * 20000.0f;
			m_waterIsExe = false;
		}
	}

	if (m_characterController.IsOnGround()) {//�L�������n�ʂɗ����Ă��鎞
		m_moveSpeed.y = 0.0f;//��ɂ͓����Ȃ�
	}
	else {
		m_moveSpeed.y -= 10.0f;//�����X�s�[�h
	}

	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_render.SetPosition(m_position);
	ManageState();
}

void Player::Magic()
{
	//�ʏ�U��
	//�N�[���^�C���񊈐�����
	if (g_pad[0]->IsTrigger(enButtonRB2) && m_bulletMagazine == true)
	{
		m_bullet = NewGO<Bullet>(0, "bullet");//�C�ۂ𐶐�
		m_bullet->SetPosition(m_position);//�ŏ���1f�����X�e�[�W�����ɔ��肪������̂�h��
		m_bulletCoolTimer = 0;//�N�[���^�C�}�[�̃��Z�b�g
		m_bulletMagazine = false;//�N�[���^�C����������
	}

	//�����@
	//�N�[���^�C���񊈐�����
	if (g_pad[0]->IsTrigger(enButtonB) && m_fireMagazine == true)
	{
		m_fire = NewGO<Fire>(0, "fire");//�����@�𐶐�
		m_fireCoolTimer = 0;//�N�[���^�C���̃��Z�b�g
		m_fireMagazine = false;//�N�[���^�C����������
		m_mp->SubMp(MP_FIRE);
	}

	//�����@
	//�N�[���^�C���񊈐�����
	if (g_pad[0]->IsTrigger(enButtonA) && m_windMagazine == true)
	{
		m_wind = NewGO<Wind>(0, "wind");//�����@�𐶐�
		m_windCoolTimer = 0;//�N�[���^�C�}�[�̃��Z�b�g
		m_windMagazine = false;//�N�[���^�C����������
		m_mp->SubMp(MP_WIND);
	}

	//�����@
	//�N�[���^�C���񊈐�����
	if (g_pad[0]->IsTrigger(enButtonY) && m_shineMagazine == true)
	{
		m_shine = NewGO<Shine>(0, "shine");//�����@�𐶐�
		m_shineCoolTimer = 0;//�N�[���^�C�}�[�̃��Z�b�g
		m_shineMagazine = false;//�N�[���^�C����������
		m_mp->SubMp(MP_SHINE);
	}
}

void Player::Rotation() 
{
	//�v���C���[�̉�]
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
	//�v���C���[�̏��
	if (m_characterController.IsOnGround() == false) {//�v���C���[���n�ʂ̏�ɗ����Ă��Ȃ���
		m_moveSpeed.y -= 1.0f;
		m_playerState = 1;//�W�����v�A�j���[�V�������Đ�����
		return;
	}
	if (fabsf(m_moveSpeed.x) >= 0.10f || fabsf(m_moveSpeed.z) >= 0.1f) {//�v���C���[��xz�̕����ɓ����Ă��鎞
		m_playerState = 2;//���s�A�j���[�V�������Đ�����
	}
	else if (m_hp->GetHP() <= 0)
	{
		m_playerState = 3;
	}
	else {//��ȊO�̎�
		m_playerState = 0;//�����A�j���[�V�������Đ�����
	}
}

void Player::PlayAnimation()
{
	//�v���C���[�̏�Ԃ̕`��
	switch (m_playerState)
	{
	case 0://�v���C���[���n�ʂ̏�ŐÎ~���Ă��鎞
		m_render.PlayAnimation(enAnimationClip_Idle);
		break;
	case 1://�v���C���[���n�ʂ̏�ɗ����Ă��Ȃ���
		m_render.PlayAnimation(enAnimationClip_Jump);
		break;
	case 2://�v���C���[��xz�̕����ɓ����Ă��鎞
		m_render.PlayAnimation(enAnimationClip_Walk);
		break;
	case 3://�v���C���[�����S������
		m_render.PlayAnimation(enAnimationClip_kneelDown);
		break;
	}
}