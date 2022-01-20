#pragma once

class TitleUi :public IGameObject
{
public:
	TitleUi();
	~TitleUi();
	bool Start();
	void Update();
	void State();
	void Timer();
	void Render(RenderContext& rc);

private:
	SpriteRender m_heart1;
	SpriteRender m_heart2;
	SpriteRender m_heart3;
	SpriteRender m_fire1;
	SpriteRender m_fire2;
	SpriteRender m_water1;
	SpriteRender m_water2;
	SpriteRender m_wind1;
	SpriteRender m_wind2;
	SpriteRender m_shine1;
	SpriteRender m_shine2;

	Vector3 m_heart1Position;
	Vector3 m_heart2Position;
	Vector3 m_heart3Position;
	Vector3 m_fire1Position;
	Vector3 m_fire2Position;
	Vector3 m_water1Position;
	Vector3 m_water2Position;
	Vector3 m_wind1Position;
	Vector3 m_wind2Position;
	Vector3 m_shine1Position;
	Vector3 m_shine2Position;

	float m_timer1 = 0;
	float m_upDown1 = 0;
	float m_timer2 = 0;
	float m_upDown2 = 0;
	float m_timer3 = 0;
	float m_upDown3 = 0;
	float m_timer4 = 0;
	float m_upDown4 = 0;
	float m_timer5 = 0;
	float m_upDown5 = 0;
};
