#pragma once

class Enemy;
class Bullet;
class Fire;
class Hp;
class Mp;
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

	//動作確認
	bool GetFire() const {
		return m_fireMagazine;
	}
	bool GetWind() const {
		return m_windMagazine;
	}
	bool GetShine() const {
		return m_shineMagazine;
	}

	//クールタイマー
	float GetFireCoolTimer() const {
		return m_fireCoolTimer;
	}
	float GetWindCoolTimer() const {
		return m_windCoolTimer;
	}
	float GetShineCoolTimer() const {
		return m_shineCoolTimer;
	}

	//MP消費量
	float GetFireMP() const {
		return MP_FIRE;
	}
	float GetWindMP() const {
		return MP_WIND;
	}
	float GetShineMP() const {
		return MP_SHINE;
	}

	const float COOLTIME_BULLET = 1.0f;
	const float COOLTIME_BRINK = 1.0f;
	const float COOLTIME_FIRE = 1.0f;
	const float COOLTIME_WIND = 1.0f;
	const float COOLTIME_SHINE = 1.0f;

	const float MP_BRINK = 5.0f;
	const float MP_FIRE = 10.0f;
	const float MP_WIND = 10.0f;
	const float MP_SHINE = 15.0f;

	Player();
	~Player();
	bool Start();
	void Update();
	void Timer();
	void Render(RenderContext& rc);
	void Move();
	void Magic();
	void Death();
	void Rotation();
	void ManageState();
	void PlayAnimation();

	//アニメーション
	enum EnAnimationClip {
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Num,
	};

private:

	//描画
	AnimationClip m_animationClips[enAnimationClip_Num];
	CharacterController m_characterController;
	Quaternion m_rotation;
	ModelRender m_render;

	//ベクトル
	Vector3 m_position;
	Vector3 m_cameraPosition;
	Vector3 m_cameraForward;
	Vector3 m_cameraRight;
	Vector3 m_bulletDirection;
	Vector3 m_moveSpeed;
	Vector3 m_forward;
	Vector3 m_right;
	Vector3 m_magicCirclePosition;
	
	//エフェクト
	EffectEmitter* m_brinkEF;
	EffectEmitter* m_coolTimeCompleteFireEF;
	EffectEmitter* m_coolTimeCompleteWindEF;
	EffectEmitter* m_coolTimeCompleteShineEF;

	//音声
	SoundSource* m_dryFireSE;
	SoundSource* m_enemyDeathSE;

	//参照
	Bullet* m_bullet;
	Fire* m_fire;
	Hp* m_hp;
	Mp* m_mp;
	Shine* m_shine;
	Wind* m_wind;

	bool m_bulletMagazine = true;
	bool m_fireMagazine = true;
	bool m_shineMagazine = true;
	bool m_windMagazine = true;
	bool m_brinkMagazine = true;

	float m_bulletCoolTimer = 1.0f;
	float m_fireCoolTimer = 10.0f;
	float m_windCoolTimer = 15.0f;
	float m_shineCoolTimer = 20.0f;
	float m_brinkCoolTimer = 5.0f;

	int m_playerState = 0;
};

