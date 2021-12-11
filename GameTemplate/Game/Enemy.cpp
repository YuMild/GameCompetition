#include "stdafx.h"
#include "Enemy.h"

#include "Bullet.h"
#include "Player.h"
#include "Fire.h"
#include "Hp.h"
#include "Map.h"
#include "Shine.h"
#include "Wind.h"
#include <random>

Enemy::Enemy() 
{
}

Enemy::~Enemy()
{
}

bool Enemy::Start()
{
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_render.Init("Assets/modelData/unityChan.tkm", m_animationClips, enAnimationClip_Num, enModelUpAxisY);
	m_enemyMap.Init("Assets/sprite/EnemyMap.dds", 200.0f, 200.0f);

	m_hp = FindGO<Hp>("hp");
	m_map = FindGO<Map>("map");
	m_player = FindGO<Player>("player");

	m_render.SetPosition(m_position);
	m_render.SetScale({ 0.5f,0.5f,0.5f });
	m_render.Update();

	//音声
	g_soundEngine->ResistWaveFileBank(11, "Assets/sound/EnemyDeath.wav");
	m_isStart = true;
	return true;
}

void Enemy::Update() 
{
	m_render.Update();
	MapMove();
	Move();
	Magic();
	Death();
	PlayAnimation();
}

void Enemy::MapMove()
{
	m_enemyMap.SetPosition({ m_position.x * -0.15f + m_map->GetMapCenterPosition().x,m_position.z * -0.15f + m_map->GetMapCenterPosition().y,0.0f });
	m_enemyMap.Update();
}

void Enemy::Render(RenderContext& rc)
{
	m_render.Draw(rc);
}

void Enemy::Move() 
{
	m_target = m_player->GetPosition() - m_position;
	m_target.Normalize();
	m_moveSpeed = m_target * 10.0f;

	g_k2Engine->DrawVector(m_target, m_player->GetPosition());

	Vector3 direction = m_moveSpeed;
	direction.y = 0.0f;
	direction.Normalize();
	Quaternion quaternion;
	quaternion.SetRotationY(atan2f(direction.x, direction.z));

	m_render.SetPosition(m_position);
	m_render.SetRotation(quaternion);
}

void Enemy::Magic()
{
	//炎魔法判定
	const auto& fireList = FindGOs<Fire>("fire");
	int fireSize = fireList.size();
	m_fireDiff = m_position - m_player->GetPosition();
	for (m_fireUnit = 0; m_fireUnit < fireSize; m_fireUnit++) {
		if (fireList[m_fireUnit]->GetMoving()==true && m_fireDiff.Length() <= 500.0f) {
			DeleteGO(this);
			m_enemyDeathSE = NewGO<SoundSource>(11);
			m_enemyDeathSE->Init(11);
			m_enemyDeathSE->Play(false);
		}
	}

	//光魔法判定
	const auto& shineList = FindGOs<Shine>("shine");
	int shineSize = shineList.size();
	m_shineMoving = false;
	//光魔法が活性化時、enemyが停止する
	for (int i = 0; i < shineSize; i++) {
		m_shineMoving = true;
	}

	//風魔法判定
	const auto& windList = FindGOs<Wind>("wind");
	int windSize = windList.size();
	m_windMoving = false;

	//風魔法が活性化時、風魔法の座標に向かう
	for (m_windUnit = 0; m_windUnit < windSize; m_windUnit++) {
		m_windDiff = windList[m_windUnit]->GetPosition() - m_position;
		m_target = windList[m_windUnit]->GetPosition() - m_position;
		m_target.Normalize();
		if (m_windDiff.Length() <= 300.0f) {
			m_shineMoving = true;
			m_moveSpeed = m_target * 2.0f;
			m_position += m_moveSpeed;
		}
	}

	//光魔法が非活性化時、動作する
	if (m_shineMoving == false) {
		m_position += m_moveSpeed * 15.0f / 30.0f;
	}
}

void Enemy::Death()
{
	//敵の死亡判定
	const auto& bulletList = FindGOs<Bullet>("bullet");
	int bulletSize = bulletList.size();
	for (int i = 0; i < bulletSize; i++) {
		Vector3 bulletdiff = bulletList[i]->GetPosition() - m_position;
		if (bulletdiff.Length() <= 75.0f) {
			DeleteGO(this);
			m_enemyDeathSE = NewGO<SoundSource>(11);
			m_enemyDeathSE->Init(11);
			m_enemyDeathSE->Play(false);
		}
	}

	Vector3 unitydiff = m_player->GetPosition() - m_position;
		if (unitydiff.Length() <= 10.0f) {
			DeleteGO(this);
			m_hp->SubHP(1);
		}
}

void Enemy::PlayAnimation()
{
	//魔法が活性化時、待機アニメーションを再生する
	if (m_shineMoving == true || m_windMoving == true) {
		m_render.PlayAnimation(enAnimationClip_Idle);
	}
	else
	{
		m_render.PlayAnimation(enAnimationClip_Walk);
	}
}