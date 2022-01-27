#pragma once

class Bullet;
class Player;
class Fire;
class Game;
class Hp;
class Map;
class Shine;
class Water;
class Wind;

/// <summary>
/// �G�@
/// </summary>
class Enemy:public IGameObject
{
public:

	/// <summary>
	/// �G�@�̍��W���擾
	/// </summary>
	/// <returns></returns>
	Vector3 GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// �G�@�̍��W���w��
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(Vector3& position) 
	{
		m_position = position;
	}

	Enemy();
	~Enemy();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// �}�b�v��̓���
	/// </summary>
	void MapMove();

	/// <summary>
	/// �}�b�v��̉摜�̓���
	/// </summary>
	/// <param name="rc"></param>
	void EnemyMap(RenderContext& rc)
	{
		if (m_isStart == false)						//	��x�������s
		{
			return;
		}
		m_enemyMap.Draw(rc);
	}

	/// <summary>
	/// �}�b�v��̃O���[�摜�̓���
	/// </summary>
	/// <param name="rc"></param>
	void EnemyMapGray(RenderContext& rc)
	{
		if (m_isStart == false)						//	��x�������s
		{
			return;
		}
		m_enemyMapGray.Draw(rc);
	}

	/// <summary>
	/// �G�@�̓���
	/// </summary>
	void Move();

	/// <summary>
	/// ���@�̑��݊m�F
	/// </summary>
	void Magic();

	/// <summary>
	/// �G�@�̎��S����
	/// </summary>
	void Death();

private:

	Quaternion m_rotation;
	ModelRender m_render;
	SpriteRender m_enemyMap;
	SpriteRender m_enemyMapGray;

	//�x�N�g��
	Vector3 m_enemyMapPosition;
	Vector3 m_target;
	Vector3 m_position;
	Vector3 m_moveSpeed;
	Vector3 m_forward;
	Vector3 m_spawnDiff;
	Vector3 m_fireDiff;
	Vector3 m_waterDiff;
	Vector3 m_windDiff;

	//�Q��
	Bullet* m_bullet;
	Fire* m_fire;
	Game* m_game;
	Hp* m_hp;
	Player* m_player;
	Shine* m_shine;
	Map* m_map;
	Water* m_water;
	Wind* m_wind;

	//����
	SoundSource* m_enemyDeathSE;

	int m_fireUnit;
	int m_waterUnit;
	int m_windUnit;
	bool m_shineMoving = false;
	bool m_windMoving = false;
	bool m_isStart = false;
	float m_fireTimer = 0.0f;
};

