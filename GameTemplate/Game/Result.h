#pragma once

class FontBlueNumber;
class FontPurpleNumber;
class Game;
class Pudding;
class Score;

/// <summary>
/// ���U���g
/// </summary>
class Result :public IGameObject
{
public:

	Result();
	~Result();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

	/// <summary>
	/// State�̊Ǘ�
	/// </summary>
	void ManageState();

private:

	SpriteRender		m_resultBackGroundRender;						//	���U���g�w�i
	SpriteRender		m_resultRender;									//	���U���g
	SpriteRender		m_timeRender;									//	�^�C��
	SpriteRender		m_puddingRender;								//	�v����
	SpriteRender		m_totalScoreRender;								//	�g�[�^���X�R�A

	//	�����N�摜
	SpriteRender		m_sRender;										//	S
	SpriteRender		m_aRender;										//	A
	SpriteRender		m_bRender;										//	B
	SpriteRender		m_cRender;										//	C
	SpriteRender		m_dRender;										//	D

	SoundSource*		m_drumRollSE			= nullptr;
	SoundSource*		m_drumSE				= nullptr;

	FontBlueNumber*		m_timeScoreFont			= nullptr;				//	�^�C���X�R�A
	FontBlueNumber*		m_puddingScoreFont		= nullptr;				//	�v�����X�R�A
	FontPurpleNumber*	m_totalScoreFont		= nullptr;				//	�g�[�^���X�R�A
	Game*				m_game					= nullptr;
	Pudding*			m_pudding				= nullptr;
	Score*				m_score					= nullptr;

	int					m_1						= 0;
	int					m_10					= 0;
	int					m_100					= 0;
	int					m_1000					= 0;
	int					m_10000					= 0;

	int					m_resultState			= 0;

	bool				m_isStart4				= true;
	bool				m_isStart5				= true;
	bool				m_isStart6				= true;

	float				m_timeScore				= 0.0f;
	float				m_puddingScore			= 0.0f;
	float				m_totalScore			= 0.0f;

	float				m_stateTimer			= 0.0f;
};