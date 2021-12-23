#pragma once

class Game;

class Hp :public IGameObject
{
public:
	void SubHP(const int subHp)
	{
		m_hp -= subHp;
	}
	int SetHP(const int setHp)
	{
		m_hp = setHp;
		return m_hp;
	}
	int GetHP() const
	{
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
	SpriteRender m_hpFrameGray[3];

	//âπê∫
	SoundSource* m_damage1SE;
	SoundSource* m_damage2SE;
	SoundSource* m_damage3SE;

	Game* m_game;

	bool m_damage1Judge = true;
	bool m_damage2Judge = true;
	bool m_damage3Judge = true;

	int m_num = 0;
	int m_hpFrameNum = 3;
	int m_hpFrameGrayNum = 3;
	int m_hp = 3;
};