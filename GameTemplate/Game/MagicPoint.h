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

	//�x�N�g��
	Vector3 m_position;
	Vector3 m_diff;

	//�G�t�F�N�g
	EffectEmitter* m_magicPointEF;
	EffectEmitter* m_magicPointDeleteEF;

	//�Q��
	Mp* m_mp;
	Player* m_player;

	float m_aliveTimer = 0;
};

