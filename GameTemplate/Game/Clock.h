#pragma once

class Game;

class Clock :public IGameObject
{
public:
	Clock();
	~Clock();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void Rotation();

private:
	SpriteRender m_clockBackGround;
	SpriteRender m_clockFrame;
	SpriteRender m_clockFrameGray;
	SpriteRender m_clockSecondHund;
	SpriteRender m_clockMinuteHund;

	Vector3 m_clockCenterPosition;
	Quaternion m_secondHundRotation;
	Quaternion m_minuteHundRotation;

	Game* m_game;

	float m_timer = 0;
	float m_secondRotation = 0;
	float m_minuteRotation = 0;
};

