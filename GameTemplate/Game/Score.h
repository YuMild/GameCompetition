#pragma once

using namespace std;

class Game;
class Pudding;

/// <summary>
/// スコア
/// </summary>
class Score : public IGameObject
{
public:

	/// <summary>
	/// プリンの獲得数に値を加算する
	/// </summary>
	/// <param name="addPuddingScore"></param>
	/// <returns></returns>
	int AddPuddingScore(const int addPuddingScore)
	{
		m_puddingScore += addPuddingScore;
		return m_puddingScore;
	}

	/// <summary>
	/// トータルスコアに値を加算する
	/// </summary>
	/// <param name="addTotalScore"></param>
	/// <returns></returns>
	float AddTotalScore(const float addTotalScore)
	{
		m_totalScoreTimer += addTotalScore;
		return m_totalScore;
	}

	/// <summary>
	/// 最終タイムスコアを取得する
	/// </summary>
	/// <returns></returns>
	int GetTimeScoreOld() const
	{
		return m_timeScoreOld;
	}

	/// <summary>
	/// 最終プリンスコアを取得する
	/// </summary>
	/// <returns></returns>
	int GetPuddingScoreOld() const
	{
		return m_puddingScoreOld;
	}

	/// <summary>
	/// 最終トータルスコアを取得する
	/// </summary>
	/// <returns></returns>
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

	int m_timeScore = 0;						//	タイムスコア
	int m_timeScoreOld = 0;						//	最終タイムスコア

	int m_puddingScore = 0;						//	プリンスコア
	int m_puddingScoreOld;						//	最終プリンスコア

	float m_totalScore = 0.0f;					//	トータルスコア
	float m_totalScoreOld = 0.0f;				//	最終トータルスコア

	float m_timeScoreTimer = 0.0f;				//	タイムスコアが出るまでの時間を計る
	float m_totalScoreTimer = 0.0f;				//	トータルスコアが出るまでの時間を計る
};

