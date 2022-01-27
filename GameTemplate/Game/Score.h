#pragma once

using namespace std;

class Game;
class Pudding;

/// <summary>
/// �X�R�A
/// </summary>
class Score : public IGameObject
{
public:

	/// <summary>
	/// �v�����̊l�����ɒl�����Z����
	/// </summary>
	/// <param name="addPuddingScore"></param>
	/// <returns></returns>
	int AddPuddingScore(const int addPuddingScore)
	{
		m_puddingScore += addPuddingScore;
		return m_puddingScore;
	}

	/// <summary>
	/// �g�[�^���X�R�A�ɒl�����Z����
	/// </summary>
	/// <param name="addTotalScore"></param>
	/// <returns></returns>
	float AddTotalScore(const float addTotalScore)
	{
		m_totalScoreTimer += addTotalScore;
		return m_totalScore;
	}

	/// <summary>
	/// �ŏI�^�C���X�R�A���擾����
	/// </summary>
	/// <returns></returns>
	int GetTimeScoreOld() const
	{
		return m_timeScoreOld;
	}

	/// <summary>
	/// �ŏI�v�����X�R�A���擾����
	/// </summary>
	/// <returns></returns>
	int GetPuddingScoreOld() const
	{
		return m_puddingScoreOld;
	}

	/// <summary>
	/// �ŏI�g�[�^���X�R�A���擾����
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

	int m_timeScore = 0;						//	�^�C���X�R�A
	int m_timeScoreOld = 0;						//	�ŏI�^�C���X�R�A

	int m_puddingScore = 0;						//	�v�����X�R�A
	int m_puddingScoreOld;						//	�ŏI�v�����X�R�A

	float m_totalScore = 0.0f;					//	�g�[�^���X�R�A
	float m_totalScoreOld = 0.0f;				//	�ŏI�g�[�^���X�R�A

	float m_timeScoreTimer = 0.0f;				//	�^�C���X�R�A���o��܂ł̎��Ԃ��v��
	float m_totalScoreTimer = 0.0f;				//	�g�[�^���X�R�A���o��܂ł̎��Ԃ��v��
};

