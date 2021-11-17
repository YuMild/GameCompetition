#pragma once

class Bullet;
class Player;
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
	void Render(RenderContext& rc);
	void Move();
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
	Vector3 m_target;
	Vector3 m_position;
	Vector3 m_moveSpeed;
	Vector3 m_forward;
	Vector3 m_spawnDiff;
	Bullet* m_bullet;
	Player* m_player;
	Wind* m_wind;
	SoundSource* m_enemyDeathSE;
	int m_windUnit;
	bool m_shineMoving = false;
	bool m_windMoving = false;
};

