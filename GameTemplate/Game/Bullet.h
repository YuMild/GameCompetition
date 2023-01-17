#pragma once
class Player;

#include "sound/SoundSource.h"

/// <summary>
/// 通常魔法
/// </summary>
class Bullet :public IGameObject
{
public:

	/// <summary>
	/// 通常魔法の座標を取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// 通常魔法の位置を指定
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	/// <summary>
	/// 通常魔法の移動速度を取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetMoveSpeed() const
	{
		return m_moveSpeed;
	}

	Bullet();
	~Bullet();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

private:

	/// <summary>
	/// 通常魔法の動作
	/// </summary>
	void Move();

	ModelRender				m_render;
	Vector3					m_position;
	Vector3					m_moveSpeed;
	Vector3					m_forward;
	Vector3					collisionPosition;

	CollisionObject*		collisionObject			= nullptr;
	EffectEmitter*			m_fireBallEF			= nullptr;
	SoundSource*			m_gunShotSE				= nullptr;
	Player*					m_player				= nullptr;

	float					m_deleteTimer			= 0.0f;
};
