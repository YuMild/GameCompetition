#include "stdafx.h"
#include "Enemy.h"

#include "Bullet.h"
#include "Player.h"
#include "Shine.h"
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


	constexpr int MIN = -300;//乱数の範囲最低値
	constexpr int MAX = 300;//乱数の範囲最大値

	constexpr int RAND_NUMS_TO_GENERATE = 2;//乱数を生成する回数

	//座標
	random_device rd;
	default_random_engine eng(rd());
	uniform_int_distribution<int> distr(MIN, MAX);
	int i = 0;
	for (int n = 0; n < RAND_NUMS_TO_GENERATE; ++n) {
		switch (i) {
		case 0:
			m_position.x = distr(eng);
			i++;
			break;
		case 1:
			m_position.z = distr(eng);
			break;
		}
	}
	m_position.y = -20.0f;
	m_render.SetPosition(m_position);//場所
	m_render.SetScale({ 0.7f,0.7f,0.7f });//サイズ
	m_render.Update();//上の情報を更新する

	//参照
	m_player = FindGO<Player>("player");

	//音声
	g_soundEngine->ResistWaveFileBank(7, "Assets/sound enemydeath.wav");

	return true;
}

void Enemy::Update() {
	m_render.Update();
	Move();
	Rotation(); 
	PlayAnimation();
}

void Enemy::Render(RenderContext& rc) {

	m_render.Draw(rc);

}

void Enemy::Move() {

	Vector3 diff = m_player->GetPosition() - m_position;
	diff.Normalize();
	m_moveSpeed = diff * 10.0f;
	if (m_enemyCanMove == true) {
		m_position += m_moveSpeed * 15.0f / 30.0f;
	}
	m_render.SetPosition(m_position);

	//光魔法判定
	const auto& shineList = FindGOs<Shine>("shine");
	int shineSize = shineList.size();
	m_enemyCanMove = true;
	for (int i = 0; i < shineSize; i++) {
			m_enemyCanMove = false;
	}
	
	//敵の死亡判定
	const auto& bulletList = FindGOs<Bullet>("bullet");
	int bulletSize = bulletList.size();
	for (int i = 0; i < bulletSize; i++) {
		Vector3 bulletdiff = bulletList[i]->GetPosition() - m_position;
		if (bulletdiff.Length() <= 100.0f) {
			DeleteGO(this);
			m_enemyDeathSE = NewGO<SoundSource>(7);
			m_enemyDeathSE->Init(7);
			m_enemyDeathSE->Play(false);
		}
	}

}

void Enemy::Rotation() {
	Vector3 m_forward = m_moveSpeed;
	m_forward.y = 0.0f;
	m_forward.Normalize();
	Quaternion quaternion;
	quaternion.SetRotationY(atan2f(m_forward.x, m_forward.z));
	m_render.SetRotation(quaternion);
}

void Enemy::PlayAnimation() {
	if (m_enemyCanMove == true) {
		m_render.PlayAnimation(enAnimationClip_Walk);
	}
	else
	{
		m_render.PlayAnimation(enAnimationClip_Idle);
	}
}