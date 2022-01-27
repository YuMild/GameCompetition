#pragma once
class Player;

#include "sound/SoundSource.h"

/// <summary>
/// �ʏ햂�@
/// </summary>
class Bullet :public IGameObject
{
public:

	/// <summary>
	/// �ʏ햂�@�̍��W���擾
	/// </summary>
	/// <returns></returns>
	Vector3 GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// �ʏ햂�@�̈ʒu���w��
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	Bullet();
	~Bullet();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// �ʏ햂�@�̓���
	/// </summary>
	void Move();

	/// <summary>
	/// �ʏ햂�@�̈ړ����x���擾
	/// </summary>
	/// <returns></returns>
	Vector3 GetMoveSpeed() const
	{
		return m_moveSpeed;
	}
private:
	ModelRender m_render;
	Vector3 m_position;
	Vector3 m_moveSpeed;
	Vector3 m_forward;
	Vector3 collisionPosition;
	CollisionObject* collisionObject;
	EffectEmitter* m_fireBallEF;
	SoundSource* m_gunShotSE;
	Player* m_player;
	//�^�C�}�[�B
	float m_deleteTimer = 0.0f;
};
