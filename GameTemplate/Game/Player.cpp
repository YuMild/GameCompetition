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
	//�A�j���[�V�����t�@�C��
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_render.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);

	//�����蔻��
	m_characterController.Init(20.0f, 5.0f, m_position);

	//����
	g_soundEngine->ResistWaveFileBank(8, "Assets/sound/damage1.wav");
	g_soundEngine->ResistWaveFileBank(9, "Assets/sound/damage2.wav");
	g_soundEngine->ResistWaveFileBank(10, "Assets/sound/damage3.wav");

	EffectEngine::GetInstance()->ResistEffect(6, u"Assets/effect/MagicCircleBrink.efk");

	//�`��
	m_render.SetPosition(m_position);//�����l��������͏����Ȃ��Ă�����
	m_position.x = 0.0f;//�����l��������͏����Ȃ��Ă�����
	m_position.y = 0.0f;//�����l��������͏����Ȃ��Ă�����
	m_position.z = 0.0f;//�����l��������͏����Ȃ��Ă�����
	m_render.SetScale({ 0.7f,0.7f,0.7f });//�����l��������͏����Ȃ��Ă�����
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
	if (m_bulletCoolTimer > 1.0f) {//�ˏo���Ă���1�b
		m_bulletMagazine = true;//�N�[���^�C����񊈐���
	}

	m_fireCoolTimer += g_gameTime->GetFrameDeltaTime();
	if (m_fireCoolTimer > 10.0f) {//�ˏo���Ă���10�b
		m_fireMagazine = true;//�N�[���^�C����񊈐���
	}

	m_windCoolTimer += g_gameTime->GetFrameDeltaTime();
	if (m_windCoolTimer > 15.0f) {//�ˏo���Ă���15�b
		m_windMagazine = true;//�N�[���^�C����񊈐���
	}

	m_shineCoolTimer += g_gameTime->GetFrameDeltaTime();
	if (m_shineCoolTimer > 20.0f) {//�ˏo���Ă���20�b
		m_shineMagazine = true;//�N�[���^�C����񊈐���
	}

	m_brinkCoolTimer += g_gameTime->GetFrameDeltaTime();
	if (m_brinkCoolTimer > 7.0f) {//�ˏo���Ă���7�b
		m_brinkMagazine = true;//�N�[���^�C����񊈐���
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

	m_cameraForward = g_camera3D->GetForward();//�O��
	m_cameraRight = g_camera3D->GetRight();//���E
	m_cameraForward.y = 0.0f;//��ɂ͓����Ȃ��悤��
	m_cameraRight.y = 0.0f;
	m_cameraForward.Normalize();
	m_cameraRight.Normalize();
	m_moveSpeed += m_cameraForward * lStickY * 150.0f;//�O��
	m_moveSpeed += m_cameraRight * lStickX * 150.0f;//���E

	//�u�Ԉړ����@
	//�N�[���^�C���񊈐�����
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

	if (m_characterController.IsOnGround()) {//�L�������n�ʂɗ����Ă��鎞
		m_moveSpeed.y = 0.0f;//��ɂ͓����Ȃ�
	}
	else {
		m_moveSpeed.y -= 2.5f;//�����X�s�[�h
	}

	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_render.SetPosition(m_position);
	ManageState();
}

void Player::Magic() {

	//�ʏ�U��
	//�N�[���^�C���񊈐�����
	if (g_pad[0]->IsTrigger(enButtonRB1) && m_bulletMagazine == true)
	{
		m_bullet = NewGO<Bullet>(0, "bullet");//�C�ۂ𐶐�
		m_bullet->SetPosition(m_position);
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
	}

	//�����@
	//�N�[���^�C���񊈐�����
	if (g_pad[0]->IsTrigger(enButtonY) && m_shineMagazine == true)
	{
		m_shine = NewGO<Shine>(0, "shine");//�����@�𐶐�
		m_shineCoolTimer = 0;//�N�[���^�C�}�[�̃��Z�b�g
		m_shineMagazine = false;//�N�[���^�C����������
	}

	//�����@
	//�N�[���^�C���񊈐�����
	if (g_pad[0]->IsTrigger(enButtonA) && m_windMagazine == true)
	{
		m_wind = NewGO<Wind>(0, "wind");//�����@�𐶐�
		m_windCoolTimer = 0;//�N�[���^�C�}�[�̃��Z�b�g
		m_windMagazine = false;//�N�[���^�C����������
	}
}

void Player::Death() {

	//���S����//
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
	//�v���C���[�̉�]
	Vector3 forward = g_camera3D->GetForward();
	forward.y = 0.0f;
	forward.Normalize();
	Quaternion quaternion;
	quaternion.SetRotationY(atan2f(forward.x, forward.z));
	m_render.SetRotation(quaternion);
}

void Player::ManageState() {
	//�v���C���[�̏��
	if (m_characterController.IsOnGround() == false) {
		//�v���C���[���n�ʂ̏�ɗ����Ă��Ȃ���
		m_playerState = 1;//�W�����v�A�j���[�V�������Đ�����
		return;
	}
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f) {
		//�v���C���[��xz�̕����ɓ����Ă��鎞
		m_playerState = 2;//���s�A�j���[�V�������Đ�����
	}
	else {//��ȊO�̎�
		m_playerState = 0;//�����A�j���[�V�������Đ�����
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
	//�v���C���[�̏�Ԃ̕`��
	switch (m_playerState) {
	case 0://�v���C���[���n�ʂ̏�ŐÎ~���Ă��鎞
		m_render.PlayAnimation(enAnimationClip_Idle);
		break;
	case 1://�v���C���[���n�ʂ̏�ɗ����Ă��Ȃ���
		m_render.PlayAnimation(enAnimationClip_Jump);
		break;
	case 2://�v���C���[��xz�̕����ɓ����Ă��鎞
		m_render.PlayAnimation(enAnimationClip_Walk);
		break;
	}
}