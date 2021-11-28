#pragma once

class Mp;
class Player;
class MagicPoint :public IGameObject
{
public:

	void SetPosition(Vector3& position) {
		m_position = position;
	}
	MagicPoint();
	~MagicPoint();
	bool Start();
	void Update();

private:

	//ベクトル
	Vector3 m_position;
	Vector3 m_diff;

	//エフェクト
	EffectEmitter* m_magicPointEF;
	EffectEmitter* m_magicPointDeleteEF;

	//参照
	Mp* m_mp;
	Player* m_player;

	float m_aliveTimer = 0;
};

