#pragma once
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
	Vector3 m_position;
	EffectEmitter* m_magicPointEF;

	float m_aliveTimer = 0;
};

