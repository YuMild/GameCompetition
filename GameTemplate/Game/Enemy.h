#pragma once

class Bullet;
class Player;
class Fire;
class Map;
class Shine;
class Wind;

class Enemy:public IGameObject
{
public:
	void SetPosition( Vector3 & position) {
		m_position = position;
	}
	Vector3 GetPosition() const {
		return m_position;
	}
	Enemy();
	~Enemy();
	bool Start();
	void Update();
	void MapMove();
	void Render(RenderContext& rc);
	void Move();
	void Magic();
	void Death();
	void PlayAnimation();
	enum EnAnimationClip {
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Num,
	};

private:
	AnimationClip m_animationClips[enAnimationClip_Num];
	Quaternion m_rotation;
	ModelRender m_render;
	SpriteRender m_enemyMap;
	Vector3 m_enemyMapPosition;
	Vector3 m_target;
	Vector3 m_position;
	Vector3 m_moveSpeed;
	Vector3 m_forward;
	Vector3 m_spawnDiff;
	Vector3 m_fireDiff;
	Vector3 m_windDiff;
	Bullet* m_bullet;
	Fire* m_fire;
	Player* m_player;
	Shine* m_shine;
	Map* m_map;
	Wind* m_wind;
	SoundSource* m_enemyDeathSE;
	int m_fireUnit;
	int m_windUnit;
	bool m_shineMoving = false;
	bool m_windMoving = false;
	float m_fireTimer = 0.0f;
};

