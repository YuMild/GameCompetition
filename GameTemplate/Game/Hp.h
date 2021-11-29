#pragma once

class Hp :public IGameObject
{
public:
	void SubHP(const int setHp) {
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
	void Damage();

private:
	//âÊëú
	SpriteRender m_hpInside[3];
	SpriteRender m_hpFrame[3];

	//âπê∫
	SoundSource* m_damage1SE;
	SoundSource* m_damage2SE;
	SoundSource* m_damage3SE;

	bool m_damage1Judge = true;
	bool m_damage2Judge = true;
	bool m_damage3Judge = true;

	int m_num = 0;
	int m_frameNum = 3;
	int m_hp = 3;
};