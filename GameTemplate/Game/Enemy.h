#pragma once
class Enemy:public IGameObject
{
public:
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
	Vector3 m_target;
	Vector3 m_forward;
	Player* m_player;
};

