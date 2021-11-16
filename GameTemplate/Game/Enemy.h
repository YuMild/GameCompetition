#pragma once

class Bullet;
class Player;
class Shine;

class Enemy:public IGameObject
{
public:
	Vector3 GetPosition() const {
		return m_position;
	}
	bool GetEnemyCanMove() const{
		return m_enemyCanMove;
	}
	Enemy();
	~Enemy();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();
	void PlayAnimation();
	enum EnAnimationClip {
		enAnimationClip_Walk,
		enAnimationClip_Num,
	};

private:
	AnimationClip m_animationClips[enAnimationClip_Num];
	Quaternion m_rotation;
	ModelRender m_render;
	SpriteRender m_enemyMap;
	Vector3 m_position;
	Vector3 m_moveSpeed;
	Vector3 m_forward;
	Bullet* m_bullet;
	Player* m_player;
	SoundSource* m_enemyDeathSE;
	bool m_enemyCanMove = true;
};

