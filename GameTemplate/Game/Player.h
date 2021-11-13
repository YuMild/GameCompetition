#pragma once

class Bullet;

class Player:public IGameObject
{
public:
	Vector3 GetPosition() const
	{
		return m_position;
	}
	Player();
	~Player();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();
	void ManageState();
	void PlayAnimation();
	enum EnAnimationClip {
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Num,
	};

private:
	AnimationClip m_animationClips[enAnimationClip_Num];
	CharacterController m_characterController;
	Quaternion m_rotation;
	ModelRender m_render;
	Vector3 m_position;
	Vector3 m_cameraPosition;
	Vector3 m_bulletDirection;
	Vector3 m_moveSpeed;
	Vector3 m_forward;
	Bullet* m_bullet;
	SoundSource* m_gunShotSE;
	SoundSource* m_dryFireSE;
	SoundSource* m_enemyDeathSE;
	bool m_magazine = true;
	float m_cooltimer = 0;
	int m_playerState = 0;
};

