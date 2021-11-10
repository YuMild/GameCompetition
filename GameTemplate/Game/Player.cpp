#include "stdafx.h"
#include "Player.h"

Player::Player() {

}

Player::~Player() {

}

bool Player::Start() {
	//�A�j���[�V�����t�@�C��
	animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	render.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);

	render.SetPosition(position);
	position.x = 0.0f;
	position.y = 35.0f;
	position.z = 0.0f;

	render.SetScale({ 1.0f,1.0f,1.0f });
	render.Update();

	return true;
}

void Player::Update(){

	render.Update();
	Move();
	ManageState();
	PlayAnimation();
	Rotation();
}

void Player::Render(RenderContext& rc) {
	render.Draw(rc);
}

void Player::Move() {

	//�L�����R��
	Vector3 stickL;//�X�e�B�b�N�̓���
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();
	Vector3 forward = g_camera3D->GetForward();//�O��
	Vector3 right = g_camera3D->GetRight();//���E
	forward.y = 0.0f;//��ɂ͓����Ȃ��悤��
	right.y = 0.0f;
	forward.Normalize();
	right.Normalize();
	forward *= stickL.y * 30.0f;//�O��
	right *= stickL.x * 30.0f;//���E

	moveSpeed.x = 0.0f;
	moveSpeed.y = 0.0f;

	moveSpeed += right + forward;

	if (characterController.IsOnGround()) {//�L�������n�ʂɗ����Ă��鎞
		moveSpeed.y = 0.0f;//��ɂ͓����Ȃ�
	}
	else {
		moveSpeed.y -= 2.5f;//�����X�s�[�h
	}

	position = characterController.Execute(moveSpeed, 1.0f / 30.0f);
	render.SetPosition(position);
}

void Player::Rotation() {
	//�v���C���[�̉�]
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f) {
		rotation.SetRotationYFromDirectionXZ(moveSpeed);
		forward = Vector3::AxisZ;//������Ȃ�
		rotation.Apply(forward);//�v���C���[�������Ă������(?)
	}

	Vector3 forward = g_camera3D->GetForward();
	forward.y = 0.0f;
	forward.Normalize();
	Quaternion rotation;
	rotation.SetRotationY(atan2f(forward.x, forward.z));
	render.SetRotation(rotation);
}

void Player::ManageState() {
	//�v���C���[�̏��
	if (characterController.IsOnGround() == false) {
		//�v���C���[���n�ʂ̏�ɗ����Ă��Ȃ���
		playerState = 1;//�W�����v�A�j���[�V�������Đ�����
		return;
	}
	if (fabsf(moveSpeed.x) >= 0.001f || fabsf(moveSpeed.z) >= 0.001f) {
		//�v���C���[��xz�̕����ɓ����Ă��鎞
		playerState = 2;//���s�A�j���[�V�������Đ�����
	}
	else {//��ȊO�̎�
		playerState = 0;//�����A�j���[�V�������Đ�����
	}
}

void Player::PlayAnimation() {
	//�v���C���[�̏�Ԃ̕`��
	switch (playerState) {
	case 0://�v���C���[���n�ʂ̏�ŐÎ~���Ă��鎞
		render.PlayAnimation(enAnimationClip_Idle);
		break;
	case 1://�v���C���[���n�ʂ̏�ɗ����Ă��Ȃ���
		render.PlayAnimation(enAnimationClip_Jump);
		break;
	case 2://�v���C���[��xz�̕����ɓ����Ă��鎞
		render.PlayAnimation(enAnimationClip_Walk);
		break;
	}
}