#pragma once

class Enemy;
class Bullet;
class Shine;
class Wind;

class Player:public IGameObject
{
public:
	Vector3 GetPosition() const
	{
		return m_position;
	}
	Vector3 GetDirection() const
	{
		return m_forward;
	}
	int GetHP() const {
		return m_hp;
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
	Vector3 m_right;
	
	EffectEmitter* m_brinkEF;

	SoundSource* m_shineSE;
	SoundSource* m_dryFireSE;
	SoundSource* m_enemyDeathSE;

	SoundSource* m_damage1SE;
	SoundSource* m_damage2SE;
	SoundSource* m_damage3SE;

	Bullet* m_bullet;
	Shine* m_shine;
	Wind* m_wind;

	bool m_bulletMagazine = true;
	bool m_shineMagazine = true;
	bool m_windMagazine = true;
	bool m_brinkMagazine = true;

	bool m_1Damage = true;
	bool m_2Damage = true;
	bool m_3Damage = true;

	float m_bulletCoolTimer = 0;
	float m_shineCoolTimer = 0;
	float m_windCoolTimer = 0;
	float m_brinkCoolTimer = 0;

	int m_playerState = 0;
	int m_hp = 3;
};

