#pragma once

class Bullet;
class Enemy;
class Fire;
class Game;
class Hp;
class Mp;
class Shine;
class Water;
class Wind;

/// <summary>
///	���@
/// </summary>
class Player :public IGameObject
{
public:

	//	���̃N���X�Ŏg�p���Ă���̂�public��

	//	�N�[���^�C��
	const float COOLTIME_BULLET = 1.0f;
	const float COOLTIME_FIRE = 10.0f;
	const float COOLTIME_WATER = 3.0f;
	const float COOLTIME_WIND = 5.0f;
	const float COOLTIME_SHINE = 20.0f;

	//	MP�����
	const float MP_FIRE = 15.0f;
	const float MP_WATER = 5.0f;
	const float MP_WIND = 10.0f;
	const float MP_SHINE = 20.0f;

	/// <summary>
	/// �v���C���[�̍��W���擾
	/// </summary>
	/// <returns></returns>
	Vector3 GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// �v���C���[�̌����Ă���������擾
	/// </summary>
	/// <returns></returns>
	Vector3 GetDirection() const
	{
		return m_forward;
	}

	/// <summary>
	/// �e���@�����s����Ă��邩�m�F
	/// </summary>
	/// <returns></returns>
	bool GetFire() const {
		return m_fireMagazine;
	}
	bool GetWater() const {
		return m_waterMagazine;
	}
	bool GetWind() const {
		return m_windMagazine;
	}
	bool GetShine() const {
		return m_shineMagazine;
	}

	/// <summary>
	/// �e���@�̃N�[���^�C�����擾
	/// </summary>
	/// <returns></returns>
	float GetFireCoolTimer() const {
		return m_fireCoolTimer;
	}
	float GetWaterCoolTimer() const {
		return m_waterCoolTimer;
	}
	float GetWindCoolTimer() const {
		return m_windCoolTimer;
	}
	float GetShineCoolTimer() const {
		return m_shineCoolTimer;
	}

	/// <summary>
	/// �e���@��MP����ʂ��擾
	/// </summary>
	/// <returns></returns>
	float GetFireMP() const {
		return MP_FIRE;
	}
	float GetWaterMP() const {
		return MP_WATER;
	}
	float GetWindMP() const {
		return MP_WIND;
	}
	float GetShineMP() const {
		return MP_SHINE;
	}

	/// <summary>
	/// �v���C���[��State���w��
	/// </summary>
	/// <param name="state"></param>
	/// <returns></returns>
	int SetState(const int state) {
		m_playerState = state;
		return m_playerState;
	}

	Player();
	~Player();
	bool Start() override;
	void Update() override;
	
	void Render(RenderContext& rc) override;

private:

	/// <summary>
	/// ���Ԃ̉��Z
	/// </summary>
	void Timer();

	/// <summary>
	/// �v���C���[�̓���
	/// </summary>
	void Move();

	/// <summary>
	/// ���@
	/// </summary>
	void Magic();

	/// <summary>
	/// �v���C���[�̉�]
	/// </summary>
	void Rotation();

	/// <summary>
	/// �v���C���[�̏��
	/// </summary>
	void ManageState();

	/// <summary>
	/// �A�j���[�V����
	/// </summary>
	void PlayAnimation();

	//�A�j���[�V����
	enum EnAnimationClip {
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_kneelDown,
		enAnimationClip_Num,
	};

private:

	//�`��
	AnimationClip m_animationClips[enAnimationClip_Num];
	CharacterController m_characterController;
	Quaternion m_rotation;
	ModelRender m_render;

	//�x�N�g��
	Vector3 m_position;
	Vector3 m_cameraPosition;
	Vector3 m_cameraForward;
	Vector3 m_cameraRight;
	Vector3 m_bulletDirection;
	Vector3 m_moveSpeed;
	Vector3 m_forward;
	Vector3 m_right;
	
	//�G�t�F�N�g
	EffectEmitter* m_coolTimeCompleteFireEF;
	EffectEmitter* m_coolTimeCompleteWaterEF;
	EffectEmitter* m_coolTimeCompleteWindEF;
	EffectEmitter* m_coolTimeCompleteShineEF;

	//����
	SoundSource* m_dryFireSE;
	SoundSource* m_enemyDeathSE;

	//�Q��
	Bullet* m_bullet;
	Fire* m_fire;
	Game* m_game;
	Hp* m_hp;
	Mp* m_mp;
	Shine* m_shine;
	Water* m_water;
	Wind* m_wind;

	bool m_bulletMagazine = true;
	bool m_fireMagazine = true;
	bool m_waterMagazine = true;
	bool m_shineMagazine = true;
	bool m_windMagazine = true;
	bool m_waterIsExe = false;

	float m_bulletCoolTimer = 1.0f;
	float m_fireCoolTimer = 10.0f;
	float m_waterCoolTimer = 5.0f;
	float m_windCoolTimer = 5.0f;
	float m_shineCoolTimer = 20.0f;
	float m_waterExeTimer = 0.0f;

	int m_playerState = 0;
};

