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
	animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	enemyrender.Init("Assets/modelData/unityChan.tkm", animationClips, enAnimationClip_Num, enModelUpAxisY);
	enemymaprender.Init("Assets/sprite/enemymap.dds", 10.0f, 10.0f);
	enemymaprender.SetPosition({ 540.0f,260.0f,0.0f });

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
			enemyposition.x = distr(eng);
			i++;
			break;
		case 1:
			enemyposition.z = distr(eng);
			break;
		}
	}

	enemyrender.SetPosition(enemyposition);//場所
	enemyrender.SetScale({ 0.35f,0.35f,0.35f });//サイズ
	enemyrender.Update();//上の情報を更新する

	m_player = FindGO<Player>("player");

	return true;
}

void Enemy::Update() {
	enemyrender.Update();
	Move();
	Rotation();
	PlayAnimation();
}

void Enemy::Render(RenderContext& rc) {
	enemyrender.Draw(rc);
}

void Enemy::Move() {
	Vector3 enemydiff = m_player->playerPosition - enemyposition;
	enemydiff.Normalize();
	enemytarget = m_player->playerPosition;
	enemyMoveSpeed = enemydiff * 8.0f;
	enemyposition = enemyposition + enemyMoveSpeed * 6.0f / 30.0f;
	enemyrender.SetPosition(enemyposition);
}

void Enemy::Rotation() {
	Vector3 enemyforward = enemyMoveSpeed;
	enemyforward.y = 0.0f;
	enemyforward.Normalize();
	Quaternion rotation;
	rotation.SetRotationY(atan2f(enemyforward.x, enemyforward.z));
	enemyrender.SetRotation(rotation);
}

void Enemy::PlayAnimation() {
	enemyrender.PlayAnimation(enAnimationClip_Walk);
}