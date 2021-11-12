#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "Game.h"
#include "Background.h"
#include "sound/SoundEngine.h"

Bullet::Bullet() {
}
Bullet:: ~Bullet() {
}
bool Bullet::Start() {

	player = FindGO<Player>("player");
	render.Init("Assets/modelData/bullet.tkm");//�����_�[
	render.SetScale({ 0.35f,0.35f,0.35f });//�T�C�Y
	position = player->GetPosition();//�v���C���[�̏ꏊ�ɐ��܂��
	position.y += 0.0f;//�v���C���[��20f��ɐ��܂��

	direction = g_camera3D->GetForward();
	direction.y = 0.0f;
	direction.Normalize();

	moveSpeed = direction * 5.0f;

	return true;
}

void Bullet::Update() {

	Move();//Move�֐����X�V����
	deletetimer += g_gameTime->GetFrameDeltaTime();

	//�^�C�}�[��2.0�ȏ�ɂȂ�����B
	if (deletetimer >= 2.0f)
	{
		//���g���폜�B
		DeleteGO(this);
	}
}

void Bullet::Render(RenderContext& rc) {
	render.Draw(rc);//�`��̌�
}

void Bullet::Move() {
	direction += moveSpeed;//�C�ۂ̃X�s�[�h(�d�v)
	render.SetPosition(direction);//�`�悷��ʒu
	render.Update();//�`��̍X�V
}