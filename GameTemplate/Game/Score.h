#pragma once

using namespace std;

class Game;
class Pudding;

class Score : public IGameObject
{
public:

	//‰ÁŽZ
	int AddPuddingScore(const int addPuddingScore)
	{
		m_puddingScore += addPuddingScore;
		return m_puddingScore;
	}

	float AddTotalScore(const float addTotalScore)
	{
		m_totalScoreTimer += addTotalScore;
		return m_totalScore;
	}

	int GetTimeScoreOld() const
	{
		return m_timeScoreOld;
	}

	int GetPuddingScoreOld() const
	{
		return m_puddingScoreOld;
	}

	int GetTotalScoreOld() const
	{
		return m_totalScoreOld;
	}

	bool Start();
	void Update();

private:

	FontRender m_fontRender;

	Game* m_game;
	Pudding* m_pudding;

	int m_timeScore = 0;
	int m_timeScoreOld = 0;
	int m_puddingScore = 0;
	int m_puddingScoreOld;
	float m_totalScore = 0.0f;
	float m_totalScoreOld = 0.0f;

	float m_timeScoreTimer = 0.0f;
	float m_totalScoreTimer = 0.0f;
};

