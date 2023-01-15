#include "stdafx.h"
#include "Enemy.h"

#include "Bullet.h"
#include "Player.h"
#include "Fire.h"
#include "Game.h"
#include "Hp.h"
#include "Map.h"
#include "Shine.h"
#include "Wind.h"
#include <random>

namespace
{
	const float ENEMY_MOVESPEED = 0.5f;
	const float ENEMY_WIND_ACTIVE_MOVESPEED = 2.0f;
	const float ENEMY_SIZE = 0.5f;
	const float ENEMY_MAP_WIDTH = 200.0f;
	const float ENEMY_MAP_HEIGHT = 200.0f;
	const float ENEMY_DEATH_SE_VOLUME = 1.5f;
	const float ENEMY_DEATH_EFFECT_SIZE = 5.0f;
	const float COLLISION_JUDGE_FIRE = 500.0f;
	const float COLLISION_JUDGE_WIND = 300.0f;
	const float COLLISION_JUDGE_BULLET = 75.0f;
	const float COLLISION_JUDGE_PLAYER = 10.0f;
}

Enemy::Enemy() 
{

}

Enemy::~Enemy()
{

}

bool Enemy::Start()
{
	m_enemyMR.Init("Assets/modelData/teddyBear.tkm");
	m_enemyMap.Init("Assets/sprite/Map/EnemyMap.dds", ENEMY_MAP_WIDTH, ENEMY_MAP_HEIGHT);
	m_enemyMapGray.Init("Assets/sprite/Map/EnemyMapGray.dds", ENEMY_MAP_WIDTH, ENEMY_MAP_HEIGHT);

	m_game = FindGO<Game>("game");
	m_hp = FindGO<Hp>("hp");
	m_map = FindGO<Map>("map");
	m_player = FindGO<Player>("player");

	m_enemyMR.SetPosition(m_position);
	m_enemyMR.SetScale({ ENEMY_SIZE,ENEMY_SIZE,ENEMY_SIZE });
	m_enemyMR.Update();

	//	音声
	g_soundEngine->ResistWaveFileBank(enInitSoundNumber_EnemyDeath, "Assets/sound/EnemyDeath.wav");

	// エフェクト
	EffectEngine::GetInstance()->ResistEffect(enInitEffectNumber_EnemyDeath, u"Assets/Effect/EnemyDeath.efk");

	m_isStart = true;

	return true;
}

void Enemy::Update() 
{
	if (m_hp->GetHP() >= 1)
	{
		Move();
		Magic();
	}
	m_enemyMR.Update();
	MapMove();
	Death();
}

void Enemy::MapMove()
{
	if (m_game->GetManageState() == 0)
	{
		m_enemyMap.SetPosition({ m_position.x * -0.15f + m_map->GetMapCenterPosition().x,m_position.z * -0.15f + m_map->GetMapCenterPosition().y,0.0f });
		m_enemyMap.Update();
	}

	m_enemyMapGray.SetPosition({ m_position.x * -0.15f + m_map->GetMapCenterPosition().x,m_position.z * -0.15f + m_map->GetMapCenterPosition().y,0.0f });
	m_enemyMapGray.Update();
}

void Enemy::Render(RenderContext& rc)
{
	m_enemyMR.Draw(rc);
}

void Enemy::Move() 
{
	m_position.y = 10.0f;
	m_target = m_player->GetPosition() - m_position;
	m_target.Normalize();
	m_moveSpeed = m_target * 10.0f;
	g_k2Engine->DrawVector(m_target, m_player->GetPosition());
	m_enemyMR.SetPosition(m_position);
	Vector3 direction = m_moveSpeed;
	direction.y = 0.0f;
	direction.Normalize();
	Quaternion quaternion;
	quaternion.SetRotationY(atan2f(direction.x, direction.z));
	m_enemyMR.SetRotation(quaternion);
}

void Enemy::Magic()
{
	//	炎魔法判定
	const auto& fireList = FindGOs<Fire>("fire");
	int fireSize = fireList.size();
	m_fireDiff = m_position - m_player->GetPosition();
	for (m_fireUnit = 0; m_fireUnit < fireSize; m_fireUnit++) {
		if (fireList[m_fireUnit]->GetMoving()==true && m_fireDiff.Length() <= COLLISION_JUDGE_FIRE) {
			DeleteGO(this);
			PlayEnemyDeathSound();
			PlayEnemyDeathEffect();
		}
	}

	//	光魔法判定
	const auto& shineList = FindGOs<Shine>("shine");
	int shineSize = shineList.size();
	m_shineMoving = false;

	//	光魔法が活性化時、enemyが停止する
	for (int i = 0; i < shineSize; i++) {
		m_shineMoving = true;
	}

	//	風魔法判定
	const auto& windList = FindGOs<Wind>("wind");
	int windSize = windList.size();
	m_windMoving = false;

	//	風魔法が活性化時、風魔法の座標に向かう
	for (m_windUnit = 0; m_windUnit < windSize; m_windUnit++) {
		m_windDiff = windList[m_windUnit]->GetPosition() - m_position;
		m_target = windList[m_windUnit]->GetPosition() - m_position;
		m_target.Normalize();
		if (m_windDiff.Length() <= COLLISION_JUDGE_WIND) {
			m_windMoving = true;
			m_moveSpeed = m_target * ENEMY_WIND_ACTIVE_MOVESPEED;
			m_position += m_moveSpeed;
		}
	}

	//	光魔法が非活性化時、動作する
	if (m_shineMoving == false) {
		m_position += m_moveSpeed * ENEMY_MOVESPEED;
	}
}

void Enemy::Death()
{
	//	敵の死亡判定
	const auto& bulletList = FindGOs<Bullet>("bullet");
	int bulletSize = bulletList.size();
	for (int i = 0; i < bulletSize; i++) {
		Vector3 bulletdiff = bulletList[i]->GetPosition() - m_position;
		if (bulletdiff.Length() <= COLLISION_JUDGE_BULLET) {
			DeleteGO(this);
			PlayEnemyDeathSound();
			PlayEnemyDeathEffect();
		}
	}

	//	プレイヤーと衝突した時
	Vector3 unitydiff = m_player->GetPosition() - m_position;
	if (unitydiff.Length() <= COLLISION_JUDGE_PLAYER)
	{
		//	HPを減産する
		m_hp->SubHP(1);
		DeleteGO(this);
	}
}

void Enemy::PlayEnemyDeathSound()
{
	m_enemyDeathSE = NewGO<SoundSource>(0);
	m_enemyDeathSE->Init(enInitSoundNumber_EnemyDeath);
	m_enemyDeathSE->SetVolume(ENEMY_DEATH_SE_VOLUME);
	m_enemyDeathSE->Play(false);
}

void Enemy::PlayEnemyDeathEffect()
{
	m_enemyDeathEF = NewGO<EffectEmitter>(0);
	m_enemyDeathEF->Init(enInitEffectNumber_EnemyDeath);
	m_enemyDeathEF->SetScale(Vector3::One * ENEMY_DEATH_EFFECT_SIZE);
	m_enemyDeathEF->SetPosition(m_position);
	m_enemyDeathEF->Play();
}