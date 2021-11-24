#pragma once
class Clock :public IGameObject
{
public:
	Clock();
	~Clock();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender m_clockBackGround;
	SpriteRender m_clockFrame;
	SpriteRender m_clockMinuteHund;
	SpriteRender m_clockSecondHund;

	Vector3 m_clockCenterPosition;
};

