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
/// 敵機
/// </summary>
class Enemy:public IGameObject
{
public:

	/// <summary>
	/// 敵機の座標を取得
	/// </summary>
	/// <returns></returns>
	Vector3 GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// 敵機の座標を指定
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
	/// マップ上の動作
	/// </summary>
	void MapMove();

	/// <summary>
	/// マップ上の画像の動作
	/// </summary>
	/// <param name="rc"></param>
	void EnemyMap(RenderContext& rc)
	{
		if (m_isStart == false)						//	一度だけ実行
		{
			return;
		}
		m_enemyMap.Draw(rc);
	}

	/// <summary>
	/// マップ上のグレー画像の動作
	/// </summary>
	/// <param name="rc"></param>
	void EnemyMapGray(RenderContext& rc)
	{
		if (m_isStart == false)						//	一度だけ実行
		{
			return;
		}
		m_enemyMapGray.Draw(rc);
	}

	/// <summary>
	/// 敵機の動作
	/// </summary>
	void Move();

	/// <summary>
	/// 魔法の存在確認
	/// </summary>
	void Magic();

	/// <summary>
	/// 敵機の死亡判定
	/// </summary>
	void Death();

private:

	Quaternion		m_rotation = Quaternion::Identity;
	ModelRender		m_enemyMR;
	SpriteRender	m_enemyMap;
	SpriteRender	m_enemyMapGray;

	//音声
	SoundSource*	m_enemyDeathSE;

	//ベクトル
	Vector3			m_enemyMapPosition	= Vector3::Zero;
	Vector3			m_target			= Vector3::Zero;
	Vector3			m_position			= Vector3::Zero;
	Vector3			m_moveSpeed			= Vector3::Zero;
	Vector3			m_forward			= Vector3::Zero;
	Vector3			m_spawnDiff			= Vector3::Zero;
	Vector3			m_fireDiff			= Vector3::Zero;
	Vector3			m_waterDiff			= Vector3::Zero;
	Vector3			m_windDiff			= Vector3::Zero;

	//参照
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

