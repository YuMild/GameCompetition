#include "stdafx.h"
#include "Bullet.h"
#include "Player.h"
#include "Game.h"
#include "Background.h"
#include "sound/SoundEngine.h"
#include "graphics/effect/EffectEmitter.h"

Bullet::Bullet() {
}
Bullet:: ~Bullet() {
}
bool Bullet::Start() {

	player = FindGO<Player>("player");
	render.Init("Assets/modelData/bullet.tkm");//�����_�[
	render.SetScale({ 0.5f,0.5f,0.5f });//�T�C�Y
	position = player->GetPosition();//�v���C���[�̏ꏊ�ɐ��܂��
	position.y += 50.0f;//�v���C���[��50f��ɐ��܂��

	//�G�t�F�N�g�t�@�C��
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/fireball.efk");

	//����
	direction = g_camera3D->GetForward();
	direction.y = 0.0f;
	direction.Normalize();

	fireBallEF = NewGO<EffectEmitter>(0);
	fireBallEF->Init(0);
	
	fireBallEF->SetScale(Vector3::One * 20.0f);
	fireBallEF->Play();

	moveSpeed = direction * 20.0f;

	return true;
}

void Bullet::Update() {

	fireBallEF->SetPosition(position);

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
	position += moveSpeed;//�C�ۂ̃X�s�[�h(�d�v)
	render.SetPosition(position);//�`�悷��ʒu
	render.Update();//�`��̍X�V
}