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
	bulletRender.Init("Assets/modelData/hougan.tkm");//�����_�[
	bulletRender.SetScale({ 0.35f,0.35f,0.35f });//�T�C�Y
	bulletPosition = player->playerPosition;//�v���C���[�̏ꏊ�ɐ��܂��
	bulletPosition.y += 25.0f;//�v���C���[��20f��ɐ��܂��


	return true;
}
void Bullet::Update() {
	Move();//Move�֐����X�V����
	deleteTimer += g_gameTime->GetFrameDeltaTime();

	//�^�C�}�[��2.0�ȏ�ɂȂ�����B
	if (deleteTimer >= 2.0f)
	{
		//���g���폜�B
		DeleteGO(this);
	}
}
void Bullet::Render(RenderContext& rc) {
	bulletRender.Draw(rc);//�`��̌�
}
void Bullet::Move() {
	bulletPosition += bulletMoveSpeed;//�C�ۂ̃X�s�[�h(�d�v)
	bulletRender.SetPosition(bulletPosition);//�`�悷��ʒu
	bulletRender.Update();//�`��̍X�V
}