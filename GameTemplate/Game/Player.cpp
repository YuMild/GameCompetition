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
	//�A�j���[�V�����t�@�C��
	animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	playerrender.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);

	//�G�t�F�N�g�t�@�C��
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/explosion.efk");

	characterController.Init(20.0f, 5.0f, playerposition);//�����蔻��

	playerrender.SetPosition(playerposition);//�ꏊ
	playerposition.x = 0.0f;//���E
	playerposition.y = 35.0f;//�㉺
	playerposition.z = 0.0f;//�O��

	playerrender.SetScale({ 0.5f,0.5f,0.5f });//�T�C�Y
	playerrender.Update();//��̏����X�V����

	//�����t�@�C��
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/gunshot.wav");
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/dryfire.wav");
	g_soundEngine->ResistWaveFileBank(7, "Assets/sound/enemydeath.wav");

	return true;
}

void Player::Update() {
	//���̍X�V
	playerrender.Update();
	Move();
	ManageState();
	PlayAnimation();
	Rotation();
}

void Player::Render(RenderContext& rc) {
	//�`��̌�
	playerrender.Draw(rc);
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

	playerMoveSpeed.x = 0.0f;//������
	playerMoveSpeed.z = 0.0f;

	playerMoveSpeed += right + forward;//�S�̂̓�������

	if (characterController.IsOnGround()) {//�L�������n�ʂɗ����Ă��鎞
		playerMoveSpeed.y = 0.0f;//��ɂ͓����Ȃ�
	}
	else {
		playerMoveSpeed.y -= 2.5f;//�����X�s�[�h
	}

	playerposition = characterController.Execute(playerMoveSpeed, 1.0f / 30.0f);//�L�����N�^�[�|�W�V�����ɓ����蔻���Ǐ]������
	playerrender.SetPosition(playerposition);//�`�悷��ʒu

	//���˃N�[���^�C��
	cooltimer += g_gameTime->GetFrameDeltaTime();

	if (cooltimer > 1.0f) {//���˂��Ă���1�b
		cooltime = true;//�ēx���˂ł���悤�ɂȂ�
	}

	//�C�ۂ̔���
	if (g_pad[0]->IsTrigger(enButtonLB1)) {//�N�[���^�C����0�̎�
		if (cooltime == true) {
			m_hougan = NewGO<Hougan>(0, "hougan");//�C�ۂ𐶂ݏo��
			cameraposition = g_camera3D->GetForward();//��ɂ͓����Ȃ��悤��
			cameraposition.y = 0.0f;
			cameraposition.Normalize();
			m_hougan->moveSpeed = cameraposition * 6.5f;//�C�ۂ̈ړ��������
			cooltimer = 0;//�N�[���^�C�}�[�̏�����
			cooltime = false;//�N�[���^�C���𔭓�
			m_hougan->houganposition = playerposition;
			gunshotSE = NewGO<SoundSource>(5);
			gunshotSE->Init(5);
			gunshotSE->Play(false);
		}
		else if (cooltime == false) {//�N�[���^�C����0����Ȃ���
			dryfireSE = NewGO<SoundSource>(6);
			dryfireSE->Init(6);
			dryfireSE->Play(false);
		}
	}

	//�G�̎��S����
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
	//�v���C���[�̉�]
	if (fabsf(playerMoveSpeed.x) >= 0.001f || fabsf(playerMoveSpeed.z) >= 0.001f) {
		playerrotation.SetRotationYFromDirectionXZ(playerMoveSpeed);
		m_forward = Vector3::AxisZ;//������Ȃ�
		playerrotation.Apply(m_forward);//�v���C���[�������Ă������(?)
	}

	Vector3 forward = g_camera3D->GetForward();
	forward.y = 0.0f;
	forward.Normalize();
	Quaternion rotation;
	rotation.SetRotationY(atan2f(forward.x, forward.z));
	playerrender.SetRotation(rotation);
}

void Player::ManageState() {
	//�v���C���[�̏��
	if (characterController.IsOnGround() == false) {
		//�v���C���[���n�ʂ̏�ɗ����Ă��Ȃ���
		playerState = 1;//�W�����v�A�j���[�V�������Đ�����
		return;
	}
	if (fabsf(playerMoveSpeed.x) >= 0.001f || fabsf(playerMoveSpeed.z) >= 0.001f) {
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
		playerrender.PlayAnimation(enAnimationClip_Idle);
		break;
	case 1://�v���C���[���n�ʂ̏�ɗ����Ă��Ȃ���
		playerrender.PlayAnimation(enAnimationClip_Jump);
		break;
	case 2://�v���C���[��xz�̕����ɓ����Ă��鎞
		playerrender.PlayAnimation(enAnimationClip_Walk);
		break;
	}
}