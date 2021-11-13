#include "stdafx.h"
#include "Player.h"

#include "Bullet.h"

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

	m_characterController.Init(20.0f, 5.0f, m_position);//�����蔻��

	m_render.SetPosition(m_position);//�����l��������͏����Ȃ��Ă�����
	m_position.x = 0.0f;//�����l��������͏����Ȃ��Ă�����
	m_position.y = 0.0f;//�����l��������͏����Ȃ��Ă�����
	m_position.z = 0.0f;//�����l��������͏����Ȃ��Ă�����

	m_render.SetScale({ 1.0f,1.0f,1.0f });//�����l��������͏����Ȃ��Ă�����

	m_render.Update();

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

	//�L�����R��
	Vector3 stickL;//�X�e�B�b�N�̓���
	stickL.y = g_pad[0]->GetLStickYF();
	stickL.x = g_pad[0]->GetLStickXF();
	Vector3 forward = g_camera3D->GetForward();//�O��
	Vector3 right = g_camera3D->GetRight();//���E
	forward.y = 0.0f;//��ɂ͓����Ȃ��悤��
	right.y = 0.0f;
	forward.Normalize();
	right.Normalize();
	forward *= stickL.y * 150.0f;//�O��
	right *= stickL.x * 150.0f;//���E

	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	m_moveSpeed += right + forward;

	if (m_characterController.IsOnGround()) {//�L�������n�ʂɗ����Ă��鎞
		m_moveSpeed.y = 0.0f;//��ɂ͓����Ȃ�
	}
	else {
		m_moveSpeed.y -= 2.5f;//�����X�s�[�h
	}

	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 30.0f);
	m_render.SetPosition(m_position);

	//�N�[���^�C�}�[
	m_cooltimer += g_gameTime->GetFrameDeltaTime();

	if (m_cooltimer > 1.0f) {//�ˏo���Ă���1�b
		m_magazine = true;//�N�[���^�C����񊈐���
	}

	//�C�ۂ̔���
	if (g_pad[0]->IsTrigger(enButtonLB1)) {//�N�[���^�C���񊈐�����
		if (m_magazine == true) {
			m_bullet = NewGO<Bullet>(0, "bullet");//�C�ۂ𐶂ݏo��
			m_gunShotSE = NewGO<SoundSource>(5);
			m_gunShotSE->Init(5);
			m_gunShotSE->Play(false);
			m_cooltimer = 0;//�N�[���^�C�}�[�̃��Z�b�g
			m_magazine = false;//�N�[���^�C����������
		}
		else if (m_magazine == false) {//�N�[���^�C����������
			m_dryFireSE = NewGO<SoundSource>(6);
			m_dryFireSE->Init(6);
			m_dryFireSE->Play(false);
		}
	}
}

void Player::Rotation() {
	//�v���C���[�̉�]
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f) {
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		m_forward = Vector3::AxisZ;//������Ȃ�
		m_rotation.Apply(m_forward);//�v���C���[�������Ă������(?)
	}

	Vector3 forward = g_camera3D->GetForward();
	forward.y = 0.0f;
	forward.Normalize();
	Quaternion rotation;
	rotation.SetRotationY(atan2f(forward.x, forward.z));
	m_render.SetRotation(rotation);
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