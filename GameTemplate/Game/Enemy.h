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
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

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

private:

	/// <summary>
	/// �}�b�v��̓���
	/// </summary>
	void MapMove();

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

	/// <summary>
	/// ���S���̉������Đ�
	/// </summary>
	void PlayEnemyDeathSound();

	/// <summary>
	/// ���S���̃G�t�F�N�g���Đ�
	/// </summary>
	void PlayEnemyDeathEffect();

	Quaternion		m_rotation			= Quaternion::Identity;
	ModelRender		m_enemyMR;
	SpriteRender	m_enemyMap;
	SpriteRender	m_enemyMapGray;

	//�G�t�F�N�g
	EffectEmitter*	m_enemyDeathEF		= nullptr;

	//����
	SoundSource*	m_enemyDeathSE		= nullptr;

	//�x�N�g��
	Vector3			m_enemyMapPosition	= Vector3::Zero;
	Vector3			m_target			= Vector3::Zero;
	Vector3			m_position			= Vector3::Zero;
	Vector3			m_moveSpeed			= Vector3::Zero;
	Vector3			m_forward			= Vector3::Zero;
	Vector3			m_spawnDiff			= Vector3::Zero;
	Vector3			m_fireDiff			= Vector3::Zero;
	Vector3			m_waterDiff			= Vector3::Zero;
	Vector3			m_windDiff			= Vector3::Zero;

	//�Q��
	Bullet*			m_bullet			= nullptr;
	Fire*			m_fire				= nullptr;
	Game*			m_game				= nullptr;
	Hp*				m_hp				= nullptr;
	Player*			m_player			= nullptr;
	Shine*			m_shine				= nullptr;
	Map*			m_map				= nullptr;
	Water*			m_water				= nullptr;
	Wind*			m_wind				= nullptr;

	int				m_fireUnit			= 0;
	int				m_waterUnit			= 0;
	int				m_windUnit			= 0;
	bool			m_shineMoving		= false;
	bool			m_windMoving		= false;
	bool			m_isStart			= false;
	float			m_fireTimer			= 0.0f;
};

