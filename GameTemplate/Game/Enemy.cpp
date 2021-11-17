#include "stdafx.h"
#include "Enemy.h"

#include "Bullet.h"
#include "Player.h"
#include "Shine.h"
#include "Wind.h"
#include <random>

using namespace std;

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

	m_render.SetPosition(m_position);//場所
	m_render.SetScale({ 0.5f,0.5f,0.5f });//サイズ
	m_render.Update();//上の情報を更新する

	//音声
	g_soundEngine->ResistWaveFileBank(7, "Assets/sound enemydeath.wav");

	return true;
}

void Enemy::Update() {
	m_render.Update();
	Move();
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

	//光魔法判定
	const auto& shineList = FindGOs<Shine>("shine");
	int shineSize = shineList.size();
	m_shineMoving = false;
	for (int i = 0; i < shineSize; i++) {
		m_shineMoving = true;
	}

	//風魔法判定
	const auto& windList = FindGOs<Wind>("wind");
	int windSize = windList.size();
	m_windMoving = false;
	for (m_windUnit = 0; m_windUnit < windSize; m_windUnit++) {
		m_windMoving = true;
		//風魔法が活性化時、風魔法の座標に向かう
		if (m_windMoving == true) {
			m_target = windList[m_windUnit]->GetPosition() - m_position;
			m_target.Normalize();
			m_moveSpeed = m_target * 2.0f;
			m_position += m_moveSpeed;
		}
	}

	//光魔法が非活性化時、移動できる
	if (m_shineMoving == false) {
		m_position += m_moveSpeed * 15.0f / 30.0f;
	}

	//敵の死亡判定
	const auto& bulletList = FindGOs<Bullet>("bullet");
	int bulletSize = bulletList.size();
	for (int i = 0; i < bulletSize; i++) {
		Vector3 bulletdiff = bulletList[i]->GetPosition() - m_position;
		if (bulletdiff.Length() <= 75.0f) {
			DeleteGO(this);
			m_enemyDeathSE = NewGO<SoundSource>(7);
			m_enemyDeathSE->Init(7);
			m_enemyDeathSE->Play(false);
		}
	}

	m_render.SetPosition(m_position);
	m_render.SetRotation(quaternion);
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