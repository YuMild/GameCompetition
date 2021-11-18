#include "stdafx.h"
#include "Bullet.h"
#include "player.h"
#include "Game.h"
#include "Background.h"
#include "sound/SoundEngine.h"
#include "graphics/effect/EffectEmitter.h"

Bullet::Bullet() {
}
Bullet:: ~Bullet() {
}
bool Bullet::Start() {

	m_player = FindGO<Player>("player");
	m_render.Init("Assets/modelData/bullet.tkm");//�����_�[
	m_render.SetScale({ 0.5f,0.5f,0.5f });//�T�C�Y
	m_position = m_player->GetPosition();//�v���C���[�̏ꏊ�ɐ��܂��
	m_position.y += 50.0f;//�v���C���[��50f��ɐ��܂��

	//�]�T���o��������
	//�R���W�����̐���
	//collisionObject = NewGO<CollisionObject>(0);
	//Vector3 collisionPosition = m_position;
	//collisionObject->CreateSphere(collisionPosition);
	//collisionObject->SetName("bullet");

	//�G�t�F�N�g�t�@�C��
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/fireball.efk");

	//����
	m_forward = g_camera3D->GetForward();
	m_forward.y = 0.0f;
	m_forward.Normalize();

	//�G�t�F�N�g
	m_fireBallEF = NewGO<EffectEmitter>(0);
	m_fireBallEF->Init(0);
	m_fireBallEF->SetScale(Vector3::One * 20.0f);
	m_fireBallEF->Play();

	//����
	m_gunShotSE = NewGO<SoundSource>(6);
	m_gunShotSE->Init(6);
	m_gunShotSE->Play(false);

	m_moveSpeed = m_forward * 20.0f;

	return true;
}

void Bullet::Update() {

	m_fireBallEF->SetPosition(m_position);

	Move();//Move�֐����X�V����
	m_deleteTimer += g_gameTime->GetFrameDeltaTime();

	//�^�C�}�[��2.0�ȏ�ɂȂ�����B
	if (m_deleteTimer >= 2.0f)
	{
		//���g���폜�B
		DeleteGO(this);
	}
}

void Bullet::Render(RenderContext& rc) {
	m_render.Draw(rc);//�`��̌�
}

void Bullet::Move() {
	m_position += m_moveSpeed;//�C�ۂ̃X�s�[�h(�d�v)
	m_render.SetPosition(m_position);//�`�悷��ʒu
	m_render.Update();//�`��̍X�V
}