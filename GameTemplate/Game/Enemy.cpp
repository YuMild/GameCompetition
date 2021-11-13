#include "stdafx.h"
#include "Enemy.h"

#include "Player.h"
#include <random>

using namespace std;

Enemy::Enemy() {
	
}

Enemy::~Enemy() {

}

bool Enemy::Start() {
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_render.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);
	m_enemyMap.Init("Assets/sprite/EnemyMap.dds", 10.0f, 10.0f);
	m_enemyMap.SetPosition({ 540.0f,260.0f,0.0f });

	constexpr int MIN = -300;//乱数の範囲最低値
	constexpr int MAX = 300;//乱数の範囲最大値

	constexpr int RAND_NUMS_TO_GENERATE = 2;//乱数を生成する回数

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
	m_render.SetPosition(m_position);//場所
	m_render.SetScale({ 0.5f,0.5f,0.5f });//サイズ
	m_render.Update();//上の情報を更新する

	m_player = FindGO<Player>("player");

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
	m_target = m_player->GetPosition();
	m_moveSpeed = diff * 10.0f;
	m_position += m_moveSpeed * 5.0f / 30.0f;
	m_render.SetPosition(m_position);
}

void Enemy::Rotation() {
	Vector3 m_forward = m_moveSpeed;
	m_forward.y = 0.0f;
	m_forward.Normalize();
	Quaternion rotation;
	rotation.SetRotationY(atan2f(m_forward.x, m_forward.z));
	m_render.SetRotation(rotation);
}

void Enemy::PlayAnimation() {
	m_render.PlayAnimation(enAnimationClip_Walk);
}