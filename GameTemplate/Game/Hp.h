#pragma once
class Hp :public IGameObject
{
public:
	int SubHP(const int setHp) {
		m_hp -= setHp;
	}
	int GetHP() const {
		return m_hp;
	}
	Hp();
	~Hp();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender m_hpInside;
	SpriteRender m_hpFrame;

	int m_hp = 3;
};