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

	//�G�t�F�N�g�t�@�C��
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/fireball.efk");

	//����
	m_direction = g_camera3D->GetForward();
	m_direction.y = 0.0f;
	m_direction.Normalize();

	m_fireBallEF = NewGO<EffectEmitter>(0);
	m_fireBallEF->Init(0);
	
	m_fireBallEF->SetScale(Vector3::One * 20.0f);
	m_fireBallEF->Play();

	m_moveSpeed = m_direction * 20.0f;

	return true;
}

void Bullet::Update() {

	m_fireBallEF->SetPosition(m_position);

	Move();//Move�֐����X�V����
	m_deletetimer += g_gameTime->GetFrameDeltaTime();

	//�^�C�}�[��2.0�ȏ�ɂȂ�����B
	if (m_deletetimer >= 2.0f)
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