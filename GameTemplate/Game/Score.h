#pragma once

using namespace std;

class FontNumber;
class Pudding;

class Score : public IGameObject
{
public:

	//‰ÁŽZ
	void AddScore(const float addScore)
	{
		m_timer += addScore;
	}
	bool Start();
	void Update();
	void Output();

private:

	FontRender m_fontRender;

	FontNumber* m_fontNumber;
	Pudding* m_pudding;

	int m_score = 0;
	float m_timer = 0.0f;
};

