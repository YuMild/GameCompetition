#pragma once

class Game;

class Mp :public IGameObject
{
public:

	//‰ÁŽZ
	void AddMp(const float addMp) 
	{
		m_mp += addMp;
		if (m_mp >= 100) {
			m_mp = 100;
		}
	}
	//Œ¸ŽZ
	void SubMp(const float subMp) 
	{
		m_mp -= subMp;
		if (m_mp < 0)
		{
			m_mp = 0;
		}
	}
	float GetMP() const {
		return m_mp;
	}
	Mp();
	~Mp();
	bool Start();
	void Update();
	void Cut();
	void Heal();
	void Render(RenderContext& rc);

private:
	SpriteRender m_mpBar;
	SpriteRender m_mpBarGray;
	SpriteRender m_mpFrame;
	SpriteRender m_mpFrameGray;

	Game* m_game;

	float m_mp = 100.0f;
	float m_timer = 0.0f;
};

