#pragma once

using namespace std;

class FontNumber;
class Game;
class Pudding;

class Score : public IGameObject
{
public:

	//‰ÁŽZ
	void AddScore(const float addScore)
	{
		m_timer += addScore;
	}

	int GetScore() const
	{
		return m_score;
	}

	int GetScoreOld() const
	{
		return m_scoreOld;
	}

	bool Start();
	void Update();

private:

	FontRender m_fontRender;

	FontNumber* m_fontNumber;
	Game* m_game;
	Pudding* m_pudding;

	int m_score = 0;
	int m_scoreOld = 0;
	float m_timer = 0.0f;
};

