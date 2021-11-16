#include "stdafx.h"
#include "Player.h"

#include "Bullet.h"
#include "Shine.h"

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

	//�`��
	m_render.SetPosition(m_position);//�����l��������͏����Ȃ��Ă�����
	m_position.x = 0.0f;//�����l��������͏����Ȃ��Ă�����
	m_position.y = 0.0f;//�����l��������͏����Ȃ��Ă�����
	m_position.z = 0.0f;//�����l��������͏����Ȃ��Ă�����
	m_render.SetScale({ 1.0f,1.0f,1.0f });//�����l��������͏����Ȃ��Ă�����
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

	//�ʏ�U��

	m_bulletCoolTimer += g_gameTime->GetFrameDeltaTime();

	if (m_bulletCoolTimer > 1.0f) {//�ˏo���Ă���1�b
		m_bulletMagazine = true;//�N�[���^�C����񊈐���
	}
	
	if (g_pad[0]->IsTrigger(enButtonLB1)) {//�N�[���^�C���񊈐�����
		if (m_bulletMagazine == true) {
			m_bullet = NewGO<Bullet>(0, "bullet");//�C�ۂ𐶐�
			m_bulletCoolTimer = 0;//�N�[���^�C�}�[�̃��Z�b�g
			m_bulletMagazine = false;//�N�[���^�C����������
		}
		else if (m_bulletMagazine == false) {//�N�[���^�C����������
			m_dryFireSE = NewGO<SoundSource>(6);
			m_dryFireSE->Init(6);
			m_dryFireSE->Play(false);
		}
	}

	//�����@

	m_shineCoolTimer += g_gameTime->GetFrameDeltaTime();

	if (m_shineCoolTimer > 15.0f) {//�ˏo���Ă���1�b
		m_shineMagazine = true;//�N�[���^�C����񊈐���
	}

	if (g_pad[0]->IsTrigger(enButtonY)) {//�N�[���^�C���񊈐�����
		if (m_shineMagazine == true) {
			m_shine = NewGO<Shine>(0, "shine");//�����@�𐶐�
			m_shineSE = NewGO<SoundSource>(7);
			m_shineSE->Init(7);
			m_shineSE->Play(false);
			m_shineCoolTimer = 0;//�N�[���^�C�}�[�̃��Z�b�g
			m_shineMagazine = false;//�N�[���^�C����������
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