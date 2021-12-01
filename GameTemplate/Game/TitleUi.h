#pragma once

class TitleUi :public IGameObject
{
public:
	TitleUi();
	~TitleUi();
	bool Start();
	void Update();
	void State();
	void Move();
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

	int m_state = 0;

	float m_up = 0.0f;
	float m_down = 0.0f;
};
