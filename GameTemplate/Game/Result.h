#pragma once

class FontNumber;
class Game;
class Score;

class Result :public IGameObject
{
public:

	Result();
	~Result();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void ManageState();

private:

	SpriteRender m_resultBackGroundRender;
	SpriteRender m_resultRender;

	FontNumber* m_fontNumber;
	Game* m_game;
	Score* m_score;

	int m_1;
	int	m_10;
	int m_100;
	int m_1000;
	int m_10000;
	int m_resultState = 0;

	float m_resultScore = 0.0f;
	float m_stateTimer = 0.0f;
};