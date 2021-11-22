#include "stdafx.h"
#include "Enemy.h"

#include "Bullet.h"
#include "Player.h"
#include "Fire.h"
#include "Shine.h"
#include "Wind.h"
#include <random>

Enemy::Enemy() {
	
}

Enemy::~Enemy() {

}

bool Enemy::Start() {
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_render.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);
	m_enemyMap.Init("Assets/sprite/EnemyMap.dds", 10.0f, 10.0f);
	m_enemyMap.SetPosition({ 540.0f,260.0f,0.0f });

	m_player = FindGO<Player>("player");

	m_render.SetPosition(m_position);//�ꏊ
	m_render.SetScale({ 0.5f,0.5f,0.5f });//�T�C�Y
	m_render.Update();//��̏����X�V����

	//����
	g_soundEngine->ResistWaveFileBank(11, "Assets/sound/EnemyDeath.wav");

	return true;
}

void Enemy::Update() {
	m_render.Update();
	Move();
	Magic();
	Death();
	PlayAnimation();
}

void Enemy::Render(RenderContext& rc) {

	m_render.Draw(rc);
}

void Enemy::Move() {

	m_target = m_player->GetPosition() - m_position;
	m_target.Normalize();
	m_moveSpeed = m_target * 10.0f;

	Vector3 direction = m_moveSpeed;
	direction.y = 0.0f;
	direction.Normalize();
	Quaternion quaternion;
	quaternion.SetRotationY(atan2f(direction.x, direction.z));

	m_render.SetPosition(m_position);
	m_render.SetRotation(quaternion);
}

void Enemy::Magic() {

	//�����@����
	const auto& fireList = FindGOs<Fire>("fire");
	int fireSize = fireList.size();
	m_fireDiff = m_position - m_player->GetPosition();
	for (m_fireUnit = 0; m_fireUnit < fireSize; m_fireUnit++) {
		if (fireList[m_fireUnit]->GetMoving()==true && m_fireDiff.Length() <= 400.0f) {
			DeleteGO(this);
			m_enemyDeathSE = NewGO<SoundSource>(11);
			m_enemyDeathSE->Init(11);
			m_enemyDeathSE->SetVolume(0.1f);
			m_enemyDeathSE->Play(false);
		}
	}
			

	//�����@����
	const auto& shineList = FindGOs<Shine>("shine");
	int shineSize = shineList.size();
	m_shineMoving = false;
	for (int i = 0; i < shineSize; i++) {
		m_shineMoving = true;
	}

	//�����@����
	const auto& windList = FindGOs<Wind>("wind");
	int windSize = windList.size();
	m_windMoving = false;
	for (m_windUnit = 0; m_windUnit < windSize; m_windUnit++) {
		m_windMoving = true;
		//�����@�����������A�����@�̍��W�Ɍ�����
		if (m_windMoving == true) {
			m_target = windList[m_windUnit]->GetPosition() - m_position;
			m_target.Normalize();
			m_moveSpeed = m_target * 2.0f;
			m_position += m_moveSpeed;
		}
	}

	//�����@���񊈐������A�ړ��ł���
	if (m_shineMoving == false) {
		m_position += m_moveSpeed * 15.0f / 30.0f;
	}
}

void Enemy::Death() {

	//�G�̎��S����
	const auto& bulletList = FindGOs<Bullet>("bullet");
	int bulletSize = bulletList.size();
	for (int i = 0; i < bulletSize; i++) {
		Vector3 bulletdiff = bulletList[i]->GetPosition() - m_position;
		if (bulletdiff.Length() <= 75.0f) {
			DeleteGO(this);
			m_enemyDeathSE = NewGO<SoundSource>(11);
			m_enemyDeathSE->Init(11);
			m_enemyDeathSE->SetVolume(0.1f);
			m_enemyDeathSE->Play(false);
		}
	}
}

void Enemy::PlayAnimation() {
	if (m_shineMoving == true || m_windMoving == true) {
		m_render.PlayAnimation(enAnimationClip_Idle);
	}
	else
	{
		m_render.PlayAnimation(enAnimationClip_Walk);
	}
}