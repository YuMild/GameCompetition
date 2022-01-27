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

	Quaternion m_rotation;
	ModelRender m_render;
	SpriteRender m_enemyMap;
	SpriteRender m_enemyMapGray;

	//ベクトル
	Vector3 m_enemyMapPosition;
	Vector3 m_target;
	Vector3 m_position;
	Vector3 m_moveSpeed;
	Vector3 m_forward;
	Vector3 m_spawnDiff;
	Vector3 m_fireDiff;
	Vector3 m_waterDiff;
	Vector3 m_windDiff;

	//参照
	Bullet* m_bullet;
	Fire* m_fire;
	Game* m_game;
	Hp* m_hp;
	Player* m_player;
	Shine* m_shine;
	Map* m_map;
	Water* m_water;
	Wind* m_wind;

	//音声
	SoundSource* m_enemyDeathSE;

	int m_fireUnit;
	int m_waterUnit;
	int m_windUnit;
	bool m_shineMoving = false;
	bool m_windMoving = false;
	bool m_isStart = false;
	float m_fireTimer = 0.0f;
};

