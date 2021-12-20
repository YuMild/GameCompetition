#pragma once

class FontNumber;
class Score;

class Result :public IGameObject
{
public:

	Result();
	~Result();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:

	SpriteRender m_render;

	FontNumber* m_fontNumber;
	Score* m_score;

	int m_1;
	int	m_10;
	int m_100;
	int m_1000;
	int m_10000;

	float m_resultScore;
};