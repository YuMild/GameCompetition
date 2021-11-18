#include "stdafx.h"
#include "Player.h"

#include "Bullet.h"
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

	EffectEngine::GetInstance()->ResistEffect(2, u"Assets/effect/wind.efk");

	//�����蔻��
	m_characterController.Init(20.0f, 5.0f, m_position);

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

	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	float lStickX = g_pad[0]->GetLStickXF();
	float lStickY = g_pad[0]->GetLStickYF();

	Vector3 cameraForward = g_camera3D->GetForward();//�O��
	Vector3 cameraRight = g_camera3D->GetRight();//���E
	cameraForward.y = 0.0f;//��ɂ͓����Ȃ��悤��
	cameraRight.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.Normalize();
	m_moveSpeed += cameraForward * lStickY * 250.0f;//�O��
	m_moveSpeed += cameraRight * lStickX * 250.0f;//���E

	if (m_characterController.IsOnGround()) {//�L�������n�ʂɗ����Ă��鎞
		m_moveSpeed.y = 0.0f;//��ɂ͓����Ȃ�
	}
	else {
		m_moveSpeed.y -= 2.5f;//�����X�s�[�h
	}


	//�ʏ�U��

	m_bulletCoolTimer += g_gameTime->GetFrameDeltaTime();

	if (m_bulletCoolTimer > 1.0f) {//�ˏo���Ă���1�b
		m_bulletMagazine = true;//�N�[���^�C����񊈐���
	}

	//�N�[���^�C���񊈐�����
	if (g_pad[0]->IsTrigger(enButtonRB1) && m_bulletMagazine == true)
	{
		m_bullet = NewGO<Bullet>(0, "bullet");//�C�ۂ𐶐�
		m_bulletCoolTimer = 0;//�N�[���^�C�}�[�̃��Z�b�g
		m_bulletMagazine = false;//�N�[���^�C����������
	}
	else if (m_bulletMagazine == false) {//�N�[���^�C����������
		m_dryFireSE = NewGO<SoundSource>(7);
		m_dryFireSE->Init(7);
		m_dryFireSE->Play(false);
	}

	//�����@

	m_shineCoolTimer += g_gameTime->GetFrameDeltaTime();

	if (m_shineCoolTimer > 15.0f) {//�ˏo���Ă���1�b
		m_shineMagazine = true;//�N�[���^�C����񊈐���
	}

	//�N�[���^�C���񊈐�����
	if (g_pad[0]->IsTrigger(enButtonY) && m_shineMagazine == true)
	{
		m_shine = NewGO<Shine>(0, "shine");//�����@�𐶐�
		m_shineSE = NewGO<SoundSource>(7);
		m_shineSE->Init(7);
		m_shineSE->Play(false);
		m_shineCoolTimer = 0;//�N�[���^�C�}�[�̃��Z�b�gaa
		m_shineMagazine = false;//�N�[���^�C����������
	}

	//�����@

	m_windCoolTimer += g_gameTime->GetFrameDeltaTime();

	if (m_windCoolTimer > 10.0f) {//�ˏo���Ă���1�b
		m_windMagazine = true;//�N�[���^�C����񊈐���
	}
	
	//�N�[���^�C���񊈐�����
	if (g_pad[0]->IsTrigger(enButtonA) && m_windMagazine == true)
	{
		m_wind = NewGO<Wind>(0, "wind");//�����@�𐶐�
		m_windCoolTimer = 0;//�N�[���^�C�}�[�̃��Z�b�g
		m_windMagazine = false;//�N�[���^�C����������
	}

	//�u�Ԉړ����@

	m_brinkCoolTimer += g_gameTime->GetFrameDeltaTime();

	//�N�[���^�C��������
	if (m_brinkCoolTimer >= 7.0f) {
		m_brinkMagazine = true;
	}

	if (g_pad[0]->IsTrigger(enButtonLB1) && m_brinkMagazine == true) {

		m_brinkCoolTimer = 0.0f;
		m_brinkMagazine = false;

		m_brinkEF = NewGO<EffectEmitter>(2);
		m_brinkEF->Init(2);
		m_brinkEF->SetScale(Vector3::One * 20.0f);
		m_brinkEF->SetPosition(m_position);
		m_brinkEF->Play();

		if (m_brinkCoolTimer < 0.2f) {
			m_moveSpeed += cameraForward * 20000.0f;
		}
	}

	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	m_render.SetPosition(m_position);
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